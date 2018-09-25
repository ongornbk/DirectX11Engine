Texture2D shaderTexture;
SamplerState SampleType;



cbuffer MatrixBuffer
{
matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;
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

input.position.w = 1.0f;

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
float xd;
float yd;
xd = (960.0f - abs(input.position[0]-960.0f))/960.0f;
yd = (590.0f - abs(input.position[1]-590.0f))/590.0f;
float distance = mul(yd,xd);
distance = mul(distance,3.8f);
distance = clamp(distance,0.05f,1.05f);
return mul(distance,textureColor);
}