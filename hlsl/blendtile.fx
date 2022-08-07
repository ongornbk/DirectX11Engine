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
float4 colorVector;
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

input.position.w = 0.8f;

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
//textureColor = mul(textureColor, colorVector);
float alpha = textureColor[3];
float xd;
float yd;
//xd = (960.0f - abs(input.position[0]-960.0f))/960.0f;
//yd = (590.0f - abs(input.position[1]-590.0f))/590.0f;
xd = (960.f - abs(input.position[0]-960.f))/380.f;
yd = (590.f - abs(input.position[1]-590.f))/320.f;
float distance = mul(yd,xd);
//textureColor = mul(textureColor,0.5f);
distance = clamp(distance,0.65f,1.75f);
textureColor = mul(distance,textureColor);
textureColor[3] = alpha;
return textureColor;

}