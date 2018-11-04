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

output.position[0] = mul(output.position[0],1.0125f);
output.position[1] = mul(output.position[1],1.025f);

output.tex = input.tex;

return output;
}

float4 PSMain(PixelInputType input) : SV_TARGET
{
float4 textureColor;
textureColor = shaderTexture.Sample(SampleType,input.tex);
float alpha = textureColor[3];
textureColor[0] = 0.0f;
textureColor[1] = 0.0f;
textureColor[2] = 0.0f;
textureColor[3] = mul(textureColor[3],0.5f);
return textureColor;
}