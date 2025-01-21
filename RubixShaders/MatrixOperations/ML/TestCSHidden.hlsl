//TestCSHidden.hlsl

RWStructuredBuffer<double> inpA : register(u0);
RWStructuredBuffer<double> inpB : register(u1);
RWStructuredBuffer<double> Outp : register(u2);

[numthreads(1, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    uint index_x = DTid.x;
    double res = inpA[index_x] + inpB[index_x];
    Outp[index_x] = res;
}