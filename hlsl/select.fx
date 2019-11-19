Texture2D shaderTexture;
SamplerState SampleType;



cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer ColorBuffer : register(b1)
{
	float4 color;
};


struct VertexInputType
{
float4 position : POSITION;
float2 tex : TEXCOORD0;
};

struct PixelInputType
{
float4 position : SV_POSITION;
float2 tex : TEXCOORD0;
};

PixelInputType VSMain(VertexInputType input)
{
PixelInputType output;

input.position.w = 0.9f;

output.position = mul(input.position, worldMatrix);
output.position = mul(output.position,viewMatrix);
output.position = mul(output.position,projectionMatrix);

output.tex = input.tex;

return output;
}

float4 PSMain(PixelInputType input) : SV_TARGET
{
float4 textureColor;
textureColor = shaderTexture.Sample(SampleType,input.tex);
textureColor[0] = 1.0f;
textureColor[1] = 1.0f;
textureColor[2] = 1.0f;
textureColor[3] = mul(textureColor[3],0.5f);
return textureColor;
}