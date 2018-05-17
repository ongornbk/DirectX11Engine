#include "RendererManager.h"
#include "Timer.h"
#include "SettingsC.h"
#include "Defines.h"
#include <future>
#include <mutex>

using std::mutex;

#pragma region
class Unit;
#define UnitPtr Unit*;
#pragma endregion

namespace
{
	RendererManager*    m_instance;
	Engine*             m_engine;
	static XMVECTOR     m_cameraPosition;
	static atomic<char> m_asyncState;
	static float        m_ranges[2];
	static atomic<int>  m_coord[2];
}

RendererManager::RendererManager(Engine* engine,Shader* shader)
{
	this->m_renderingStyle = RendererManager::RenderingStyle::REVERSE;
	this->m_engine = engine;
	this->m_objects.reserve(*(SETTINGS NUMBER_OF_UNITS)+2);
	m_instance = this;
	this->m_shader = shader;
	Tile::SetGlobals(Engine::GetEngine()->GetGraphics()->GetDevice(), shader,this);
	m_map.Initialize();
	m_ui = new UserInterface(UserInterface::GAME);
	m_ui->m_interface.m_game = new UserInterfaceGame(engine, shader);
	m_ranges[0] = ((float)*(SETTINGS RESOLUTION_X) / 2.0f)+100.0f;
	m_ranges[1] = ((float)*(SETTINGS RESOLUTION_Y) / 2.0f) + 100.0f;
}


RendererManager::~RendererManager()
{
	RemoveAllObjects();
	if (m_ui)
	{
		delete m_ui;
		m_ui = NULL;
	}
}

void RendererManager::PushModel(Model * model)
{
	RenderObject object;
	object.SetRenderType(MODEL);
	object.m_model = model;
	m_objects.push_back(object);
}

void RendererManager::PushBox(CollisionBox * box)
{
	RenderObject object;
	object.SetRenderType(BOX);
	object.m_box = box;
	m_objects.push_back(object);
}

void RendererManager::PushUnit(Unit * unit)
{
	RenderObject object;
	object.SetRenderType(UNIT);
	object.m_unit = unit;
	m_objects.push_back(object);
}

extern "C"
{

	struct SortByY {
		bool  _vectorcall operator()(RenderObject &a, RenderObject &b) const noexcept {
			register float f[11];
			switch (a.m_type)
			{
			case RenderType::UNIT:
			{
				if (a.m_unit->m_model->m_flags[0])
				{
					f[0] = a.m_unit->m_model->Center.x;
					f[2] = a.m_unit->m_model->Center.y;
					f[4] = a.m_unit->m_model->Radius;
				}
				else return false;
				break;
			}
			case RenderType::MODEL:
			{
				if (a.m_model->m_flags[0])
				{
					f[0] = a.m_model->Center.x;
					f[2] = a.m_model->Center.y;
					f[4] = a.m_model->Radius;
				}
				else return false;
				break;
			}
			case RenderType::BOX:
			{
				f[0] = a.m_box->Center.x;
				f[2] = a.m_box->Center.y;
				f[4] = a.m_box->Radius;
				break;
			}

			}
			switch (b.m_type)
			{
			case RenderType::UNIT:
			{
				if (b.m_unit->m_model->m_flags[0])
				{
					f[1] = b.m_unit->m_model->Center.x;
					f[3] = b.m_unit->m_model->Center.y;
					f[5] = b.m_unit->m_model->Radius;
				}
				else return false;
				break;
			}
			case RenderType::MODEL:
			{
				if (b.m_model->m_flags[0])
				{
					f[1] = b.m_model->Center.x;
					f[3] = b.m_model->Center.y;
					f[5] = b.m_model->Radius;
				}
				else return true;
				break;
			}
			case RenderType::BOX:
			{
				f[1] = b.m_box->Center.x;
				f[3] = b.m_box->Center.y;
				f[5] = b.m_box->Radius;
				break;
			}
			}
			f[6] = f[0] - f[1];
			f[7] = f[2] - f[3];
			f[8] = sqrt((f[6] * f[6]) + (f[7] * f[7]));
			f[9] = (f[4] + f[5]);
			if (f[8] < f[9])
			{
				f[10] = f[8] - f[9];
				if (a.IsPushable())
				{
					if (b.IsPushable())
					{
						f[10] /= 2.0f;
						if (f[0] < f[1])
						{
							a.TranslateXPlus(f[10]);
							b.TranslateXMinus(f[10]);

						}
						else
						{
							a.TranslateXMinus(f[10]);
							b.TranslateXPlus(f[10]);

						}
						a.Update();
						b.Update();
					}
					else
					{
						if (f[0] < f[1]) a.TranslateXPlus(f[10]);
						else         a.TranslateXMinus(f[10]);

						a.Update();
					}
				}
				else
				{
					if (b.IsPushable())
					{
						if (f[0] < f[1]) b.TranslateXMinus(f[10]);
						else         b.TranslateXPlus(f[10]);


						b.Update();
					}
					else
					{

					//	a.GoBack();
					//	b.GoBack();
					}
				}
			//	a.Block();
			//	b.Block();
			}
			else
			{
				//a.Block(false);
				//b.Block(false);
			}
			return f[2] > f[3];
		}
	};

	struct SortByX {
		bool _vectorcall operator()(RenderObject  &a, RenderObject  &b) const noexcept {
			register float f[11];
			switch (a.m_type)
			{
			case RenderType::UNIT:
			{
				if (a.m_unit->m_model->m_flags[0])
				{
					f[0] = a.m_unit->m_model->Center.x;
					f[2] = a.m_unit->m_model->Center.y;
					f[4] = a.m_unit->m_model->Radius;
				}
				else return false;
				break;
			}
			case RenderType::MODEL:
			{
				if (a.m_model->m_flags[0])
				{
					f[0] = a.m_model->Center.x;
					f[2] = a.m_model->Center.y;
					f[4] = a.m_model->Radius;
				}
				else return false;
				break;
			}
			case RenderType::BOX:
			{
				f[0] = a.m_box->Center.x;
				f[2] = a.m_box->Center.y;
				f[4] = a.m_box->Radius;
				break;
			}

			}
			switch (b.m_type)
			{
			case RenderType::UNIT:
			{
				if (b.m_unit->m_model->m_flags[0])
				{
					f[1] = b.m_unit->m_model->Center.x;
					f[3] = b.m_unit->m_model->Center.y;
					f[5] = b.m_unit->m_model->Radius;
				}
				else return false;
				break;
			}
			case RenderType::MODEL:
			{
				if (b.m_model->m_flags[0])
				{
					f[1] = b.m_model->Center.x;
					f[3] = b.m_model->Center.y;
					f[5] = b.m_model->Radius;
				}
				else return true;
				break;
			}

			case RenderType::BOX:
			{
				f[1] = b.m_box->Center.x;
				f[3] = b.m_box->Center.y;
				f[5] = b.m_box->Radius;
			}
			}
			f[6] = f[0] - f[1];
			f[7] = f[2] - f[3];
			f[8] = sqrt((f[6] * f[6]) + (f[7] * f[7]));
			f[9] = (f[4] + f[5]);
			if (f[8] < f[9])
			{
				f[10] = f[8] - f[9];
				if (a.IsPushable())
				{
					if (b.IsPushable())
					{
						f[10] /= 2.0f;
						if (f[2] < f[3])
						{
							a.TranslateYPlus(f[10]);
							b.TranslateYMinus(f[10]);

						}
						else
						{
							a.TranslateYMinus(f[10]);
							b.TranslateYPlus(f[10]);

						}


						//a.Update();
						//b.Update();
					}
					else
					{
						if (f[2] < f[3]) a.TranslateYPlus(f[10]);
						else         a.TranslateYMinus(f[10]);

						//a.Update();
						//a.Block();
						//b.Block();
					}
				}
				else
				{
					if (b.IsPushable())
					{
						if (f[2] < f[3]) b.TranslateYMinus(f[10]);
						else             b.TranslateYPlus(f[10]);

						//b.Update();
						//a.Block();
						//b.Block();
					}
					else
					{
					//	a.Block();
					//	b.Block();
					//	a.GoBack();
					//	b.GoBack();
					}
				}
			}
			else
			{
			//	a.Block(false);
			//	b.Block(false);
			}
			return  f[0] > f[1];
		}
	};


//deprecated
#pragma region
	struct SortByXY {
		bool operator()(RenderObject const &a, RenderObject const &b) const noexcept {
			float ax, bx;
			float ay, by;
			float ar, br;
			float distanceX = 0.0f, distanceY = 0.0f, distance = 0.0f;
			float collisionSum = 0.0f;
			float offsetX = 0.0f, offsetY = 0.0f;
			switch (a.m_type)
			{
			case RenderType::MODEL:
			{
				if (a.m_model->m_flags[0])
				{
					ax = a.m_model->Center.x;
					ay = a.m_model->Center.y;
					ar = a.m_model->Radius;
				}
				else return false;
				break;
			}

			}
			switch (b.m_type)
			{
			case RenderType::MODEL:
			{
				if (b.m_model->m_flags[0])
				{
					bx = b.m_model->Center.x;
					by = b.m_model->Center.y;
					br = b.m_model->Radius;
				}
				else return true;
				break;
			}
			}
			distanceX = ax - bx;
			distanceY = ay - by;
			float aspect_ratio = distanceX / distanceY;
			distance = sqrt((distanceX*distanceX) + (distanceY*distanceY));
			collisionSum = (ar + br);
			if (distance < collisionSum)
			{
				offsetX = distance - collisionSum;
				offsetX *= aspect_ratio;
				offsetY /= aspect_ratio;
				if (a.m_model->m_flags[2])
				{
					if (b.m_model->m_flags[2])
					{
						offsetX /= 2.0f;
						offsetY /= 2.0f;
						if (ay < by)
						{
						//	a.m_model->Center.y += offsetY;
						//	b.m_model->Center.y -= offsetY;
						}

						else
						{
						//	a.m_model->Center.y -= offsetY;
						//	b.m_model->Center.y += offsetY;
						}
						if (ax < bx)
						{
						//	a.m_model->Center.x += offsetX;
						//	b.m_model->Center.x -= offsetX;
						}
						else
						{
						//	a.m_model->Center.x -= offsetX;
						//	b.m_model->Center.x += offsetX;
						}
					//	a.m_model->UpdatePosition();
					//	b.m_model->UpdatePosition();
					}
					else
					{
					//	if (ay < by) a.m_model->Center.y += offsetY;
					//	else         a.m_model->Center.y -= offsetY;
					//	if (ax < bx) a.m_model->Center.x += offsetX;
					//	else         a.m_model->Center.x -= offsetX;

					//	a.m_model->UpdatePosition();
					}
				}
				else
				{
					if (b.m_model->m_flags[2])
					{
					//	if (ay < by) b.m_model->Center.y -= offsetY;
					//	else         b.m_model->Center.y += offsetY;
					//	if (ay < by) b.m_model->Center.x -= offsetX;
					//	else         b.m_model->Center.x += offsetX;

					//	b.m_model->UpdatePosition();
					}
					else
					{

					}
				}
			}
			return ay > by;
		}
	};
#pragma endregion 

	bool _vectorcall validateRendering(XMFLOAT3 object) noexcept
	{
		register float f[2];
		f[0] = abs((object.x) - (m_cameraPosition.m128_f32[0]));
		f[1] = abs((object.y) - (m_cameraPosition.m128_f32[1]));
		if ((f[0] > m_ranges[0])||(f[1] > m_ranges[1]))
			return false;
		else return true;
	}

}

	void RendererManager::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
	{
		
		m_shader->Begin(deviceContext);
	//	m_shader->SetShaderParameters(deviceContext, 1.0f, 1.0f, 1.0f, 1.0f);//Aint feckin workin
		m_map.Render(deviceContext, viewMatrix, projectionMatrix,m_cameraPosition);
		GRAPHICS EnableAlphaBlending(true);
		//RenderObject* _previous = NULL;
		//float distanceX = 0.0f, distanceY = 0.0f, distance = 0.0f;
		//float collisionSum = 0.0f;
		//float offset = 0.0f;
		for (auto &&object : m_objects)
		{
			switch (object.m_type)
			{
			case RenderType::MODEL:
			{
				//if (object.m_model->m_enabledRendering)
				//{
					//if (_previous)
					//{
						//distanceX    = ((_previous->m_model->Center.x) - (object.m_model->Center.x));
						//distanceY    = ((_previous->m_model->Center.y) - (object.m_model->Center.y));
						//distance     = sqrt((distanceX*distanceX) + (distanceY*distanceY));
						//collisionSum = (_previous->m_model->Radius + object.m_model->Radius);
						//if (distance < collisionSum)
					//	{
							//offset = distance - collisionSum;
							//object.m_model->Center.x -= sqrt((offset*offset) - (distanceY*distanceY))/2.0f;
							//_previous->m_model->Center.x += sqrt((offset*offset) - (distanceY*distanceY)) / 2.0f;
							//_previous->m_model->UpdatePosition();
						//	object.m_model->UpdatePosition();
					//	}
					//}

				//	object.m_model->m_selectedStance = object.m_model->Contains(cursorPosition);
					object.m_model->Render(deviceContext, viewMatrix, projectionMatrix, m_shader);
					//_previous = &object;
				//}
			

			break;
			}
			case RenderType::UNIT:
			{
				object.m_unit->GetModel()->Render(deviceContext, viewMatrix, projectionMatrix, m_shader);
			}
		}
	}
		m_ui->Render(deviceContext, viewMatrix, projectionMatrix);

m_shader->End(deviceContext);
GRAPHICS EnableAlphaBlending(false);
}

	extern "C"
	{

		void _vectorcall UpdatePart(std::vector<RenderObject> &vec,float dt) noexcept
		{
			int mousePosition[2];
			UserInterfaceGame::GetMousePosition(mousePosition[0],mousePosition[1]);
			FXMVECTOR point = XMVectorSet((float)mousePosition[0], (float)mousePosition[1], 0.0f, 0.0f);
			for (auto i = vec.begin(); i < vec.end(); ++i)
			{
				switch ((*i).m_type)
				{
				case RenderType::UNIT:
				{

					if ((*i).m_unit)
					{
						(*i).m_unit->Update();
						Model* model = (*i).m_unit->GetModel();
						model->Update(dt);
						model->SetRenderingStance(validateRendering(model->GetPosition()));
						if (model->Contains(point))
						{
							//model->GoBack(); //Mouse stops units ..... usefull bugg
							if (model->Contains(point))
							{
								model->m_flags[1] = true;
								GLOBAL m_lastSelectedUnit = (*i).m_unit;
							}
							else
							{
								model->m_flags[1] = false;
							}
						}
						else
						{
							model->m_flags[1] = false;
						}

					}
					else
					{
						vec.erase(i);
						i--;
					}
					break;
				}
				case RenderType::MODEL:
				{
					if ((*i).m_model)
					{
						
						Model* model = (*i).m_model;
						model->Update(dt);
						model->SetRenderingStance(validateRendering(model->GetPosition()));
						if (model->Contains(point))
						{
							model->GoBack();
							if (model->Contains(point))
							{
								model->m_flags[1] = true;
								GLOBAL m_lastSelectedUnit = (*i).m_unit;
							}
							else
							{
								model->m_flags[1] = false;
							}
						}
						else
						{
							model->m_flags[1] = false;
						}
						
					}
					else
					{
						vec.erase(i);
						i--;
					}
					break;
				}
				}
			}
			m_asyncState++;
		}


}

void RendererManager::Update()
{
#pragma region
	using std::async;
	using std::vector;
	using std::advance;
	using std::sort;
#pragma endregion
	m_asyncState = 0;
	m_cameraPosition = CAMERA GetPosition();
	m_ui->Update(m_cameraPosition);
	float dt = Timer::GetDeltaTime();


	size_t middle = m_objects.size() / 2;
	vector<RenderObject>::const_iterator middleIter(m_objects.cbegin());
	advance(middleIter, middle);

	vector<RenderObject> leftHalf(m_objects.cbegin(), middleIter);
	vector<RenderObject> rightHalf(middleIter, m_objects.cend());

	async(launch::async,UpdatePart, leftHalf,dt);
	async(launch::async,UpdatePart, rightHalf, dt);
	while (m_asyncState != 2)
	{
		std::this_thread::sleep_for(1ms);
	}

	if (m_renderingStyle == RendererManager::RenderingStyle::REVERSE)
	{
		std::reverse(m_objects.begin(), m_objects.end());
	}
	sort(m_objects.begin(), m_objects.end(), SortByX());
	sort(m_objects.begin(), m_objects.end(), SortByY());


}

void RendererManager::RemoveAllObjects()
{
	for (auto &&object : m_objects)
	{
		switch (object.m_type)
		{
		case RenderType::UNIT:
		delete object.m_unit;
		break;
		case RenderType::MODEL:
			delete object.m_model;
			break;
		case RenderType::BOX:
			delete object.m_box;
			break;
		}
	}
	m_objects.clear();
}

void RendererManager::SetRenderingStyle(RenderingStyle render)
{
	m_renderingStyle = render;
}

RendererManager * RendererManager::GetInstance()
{
	return m_instance;
}


