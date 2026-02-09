
matrix WorldMatrix, ViewMatrix, ProjMatrix;

struct VS_Input
{
    float3 vPos : POSITION;
    float3 vColor : COLOR;
};

struct VS_Output
{
    float4 vPos : SV_Position;
    float3 vColor : COLOR;
};

VS_Output VS_Shader(VS_Input Input)
{
    VS_Output Output = (VS_Output)0;
    
    vector vPos = mul(float4(Input.vPos, 1.f), WorldMatrix);
    vPos = mul(vPos, ViewMatrix);
    vPos = mul(vPos, ProjMatrix);
    
    Output.vPos = vPos;
    Output.vColor = Input.vColor;
    
    return Output;
}

struct PS_Output
{
    float4 vColor : SV_TARGET0;
};

PS_Output PS_Shader(VS_Output Input)
{
    PS_Output Output = (PS_Output) 0;
    
    Output.vColor = float4(Input.vColor, 1.f);
    
    return Output;
}

technique11 DefaultTechnique
{
    pass DefaultPass
    {
        VertexShader = compile vs_5_0 VS_Shader();
        PixelShader = compile ps_5_0 PS_Shader();
    }
}