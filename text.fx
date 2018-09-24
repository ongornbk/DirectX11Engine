Texture2D shaderTexture;
SamplerState SampleType;



cbuffer MatrixBuffer
{
matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;
};

cbuffer CameraBuffer
{
float cameraX;
float cameraY;
float cameraZ;
float globalLight;
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
return mul(1.5f,textureColor);

}