const float SCREEN_WIDTH = 1280.f;
const float SCREEN_HEIGHT = 720.f;

float4x4 proj;
float4x4 world;

texture tex;
float uv_left;
float uv_top;
float uv_width;
float uv_height;
float alpha;
float red;
float green;
float blue;
float scaleX;
float scaleY;
float a;
int mm = 14;

sampler smp = sampler_state {
	texture = <tex>;
	MinFilter = LINEAR;
	//MagFilter = LINEAR;
	MipFilter = NONE;
};


struct VS_IN {
	float3 pos : POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_OUT {
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
};

struct PS_IN {
	float4 color : COLOR0;
	float2 uv : TEXCOORD0;
	float2 pos : VPOS;
};

/* -- 頂点シェーダ -- */

VS_OUT vs_main(VS_IN In) {
	VS_OUT Out = (VS_OUT)0;
	mm = 1;

	Out.pos = mul(float4(In.pos, 1.f), world);
	Out.pos = mul(Out.pos, proj);
	Out.uv = In.uv * float2(uv_width, uv_height) + float2(uv_left, uv_top);
	return Out;
}


/* -- ピクセルシェーダ -- */

//乗算
float4 ps_mul(PS_IN In) : COLOR0{
	//mm = 100;
	float4 color = tex2D(smp, In.uv);
	color.a *= alpha;
	color.r *= red;
	color.g *= green;
	color.b *= blue;
	return color;
}

//加算
float4 ps_plus(VS_OUT In) : COLOR0{
	float4 color = tex2D(smp, In.uv);
	color.a *= alpha;
	color.r += red;
	color.g += green;
	color.b += blue;
	return color;
}

//減算
float4 ps_minus(VS_OUT In) : COLOR0{
	float4 color = tex2D(smp, In.uv);
	color.a *= alpha;
	color.r -= red;
	color.g -= green;
	color.b -= blue;
	return color;
}

//除算
float4 ps_div(VS_OUT In) : COLOR0{
	float4 color = tex2D(smp, In.uv);
	color.a *= alpha;
	color.r /= red;
	color.g /= green;
	color.b /= blue;
	return color;
}

//反転
float4 ps_neg(VS_OUT In) : COLOR0{
	float4 color = tex2D(smp, In.uv);
	color.a *= alpha;
	color.r = 1.f - color.r;
	color.g = 1.f - color.g;
	color.b = 1.f - color.b;
	return color;
}

//モノクロ
float4 ps_mono(VS_OUT In) : COLOR0{
	float4 color = tex2D(smp, In.uv);

	float Y = (0.299f * color.r) + (0.587f * color.g) + (0.114f * color.b);
	float I = //(0.596f * color.r) - (0.274f * color.g) + (0.322f * color.b);
		0.0f;
	float Q = //(0.211f * color.r) + (0.522f * color.g) + (0.311f * color.b);
		0.0f;

	color.a *= alpha;
	color.r = Y + (0.956f * I) + (0.620f * Q);
	color.g = Y - (0.272f * I) - (0.647f * Q);
	color.b = Y - (1.108f * I) + (1.705f * Q);

	return color;
}

//セピア
float4 ps_sepia(VS_OUT In) : COLOR0{
	float4 color = tex2D(smp, In.uv);

	float Y = (0.299f * color.r) + (0.587f * color.g) + (0.114f * color.b);
	float I = //(0.596f * color.r) - (0.274f * color.g) - (0.322f * color.b);
		0.1f;
	float Q = //(0.211f * color.r) - (0.522f * color.g) + (0.311f * color.b);
		0.0f;

	color.a *= alpha;
	color.r = Y + (0.956f * I) + (0.620f * Q);
	color.g = Y - (0.272f * I) - (0.647f * Q);
	color.b = Y - (1.108f * I) + (1.705f * Q);

	return color;
}


technique Tech {
	pass p0
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_mul();
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		CullMode = CCW;
		Lighting = false;
		ZEnable = true;
		ZWriteEnable = false;
	}

	pass p1
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_div();

		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		CullMode = CCW;
		Lighting = false;
		ZEnable = true;
		ZWriteEnable = false;
	}
	
	pass p2
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_plus();

		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		CullMode = CCW;
		Lighting = false;
		ZEnable = true;
		ZWriteEnable = false;
	}

	pass p3
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_minus();

		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		CullMode = CCW;
		Lighting = false;
		ZEnable = true;
		ZWriteEnable = false;
	}

	pass p4
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_neg();

		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		CullMode = CCW;
		Lighting = false;
		ZEnable = true;
		ZWriteEnable = false;
	}

	pass p5
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_mono();

		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		CullMode = CCW;
		Lighting = false;
		ZEnable = true;
		ZWriteEnable = false;
	}

	pass p6
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_sepia();

		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		CullMode = CCW;
		Lighting = false;
		ZEnable = true;
		ZWriteEnable = false;
	}
}