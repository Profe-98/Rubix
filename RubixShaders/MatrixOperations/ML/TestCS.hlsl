//TestCS.hlsl for MatrixInputLayers

RWStructuredBuffer<double> Input : register(u0);
RWStructuredBuffer<double> Output : register(u1);

[numthreads(1, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    uint index_x = DTid.x;
    uint index_y = DTid.y;
    double val_in = Input[index_x * index_y];
    Output[index_x * index_y] = val_in;
}