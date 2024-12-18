//MatrixAdd.hlsl

#pragma Target 5.0


RWStructuredBuffer<float> BufferInputA : register(u0);
RWStructuredBuffer<float> BufferInputB : register(u1);
RWStructuredBuffer<float> BufferOutput : register(u2);



[numthreads(1, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint index = DTid.x;
    float valA = BufferInputA[index];
    float valB = BufferInputB[index];
    float valC = valA + valB;
    BufferOutput[index] = valC;
}