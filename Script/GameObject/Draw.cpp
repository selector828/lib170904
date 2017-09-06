#include "Draw.h"
#include "..\..\Lib\DirectX.h"
#include "..\..\Lib\Texture.h"
#include "..\..\Lib\GameObject.h"
#include "..\..\Lib\Camera.h"

DrawScript ds;

void DrawScript::Init(GameObject * _this)
{
	_this->SetParam("TextureName", "hime");
	_this->SetParam("Pattern", 0.f);
	_this->SetParam("ScaleX", 1.f);
	_this->SetParam("ScaleY", 1.f);
	_this->SetParam("ScrollX", 0.f);
	_this->SetParam("ScrollY", 0.f);
	_this->SetParam("Layer", "Default");
	_this->SetParam("Shader", 0);
	_this->SetParam("Angle", 0.f);
	_this->SetParam("ColorR", 1.f);
	_this->SetParam("ColorG", 1.f);
	_this->SetParam("ColorB", 1.f);
	_this->SetParam("ColorA", 1.f);
}

void DrawScript::Draw(GameObject * _this)
{


	//�e�N�X�`���̗L���m�F
	if (Texture::GetTexture() == NULL)
		return;

	//�e�N�X�`�����̓o�^
	_this->SetParam("DivX", Texture::Instance()->TexturesInfo[_this->GetParam<string>("TextureName")].Div.x);
	_this->SetParam("DivY", Texture::Instance()->TexturesInfo[_this->GetParam<string>("TextureName")].Div.y);
	_this->SetParam("StartU", Texture::Instance()->TexturesInfo[_this->GetParam<string>("TextureName")].StartUV.x);
	_this->SetParam("StartV", Texture::Instance()->TexturesInfo[_this->GetParam<string>("TextureName")].StartUV.y);
	_this->SetParam("SizeX", Texture::Instance()->TexturesInfo[_this->GetParam<string>("TextureName")].TextureSize.x);
	_this->SetParam("SizeY", Texture::Instance()->TexturesInfo[_this->GetParam<string>("TextureName")].TextureSize.y);

	// ���[���h�ϊ��s��쐬
	D3DXMATRIX world, scale, rot, pos;
	D3DXMatrixScaling(&world,
		_this->GetParam<float>("SizeX"), _this->GetParam<float>("SizeY"), 1.f);
	D3DXMatrixScaling(&scale, _this->GetParam<float>("ScaleX"), _this->GetParam<float>("ScaleY"), 1.f);

	//�e�q�֌W�m�F
	if (_this->GetParent() != nullptr)
	{
		//���C���[�m�F
		if (_this->GetParam<string>("Layer") == "Default")
			D3DXMatrixTranslation(&pos, _this->GetParam<float>("PositionX") - (Camera::Position().x - SCREEN_WIDTH * .5f) + _this->GetParent()->GetParam<float>("PositionX"),
				_this->GetParam<float>("PositionY") - (Camera::Position().y - SCREEN_HEIGHT * .5f) + _this->GetParent()->GetParam<float>("PositionY"), 0.f); //���W
		else
			D3DXMatrixTranslation(&pos, _this->GetParam<float>("PositionX") + _this->GetParent()->GetParam<float>("PositionX"),
				_this->GetParam<float>("PositionY") + _this->GetParent()->GetParam<float>("PositionY"), 0.f); //���W
	}
	else
	{
		//���C���[�m�F
		if (_this->GetParam<string>("Layer") == "Default")
			D3DXMatrixTranslation(&pos, _this->GetParam<float>("PositionX") - (Camera::Position().x - SCREEN_WIDTH * .5f),
				_this->GetParam<float>("PositionY") - (Camera::Position().y - SCREEN_HEIGHT * .5f), 0.f); //���W
		else
			D3DXMatrixTranslation(&pos, _this->GetParam<float>("PositionX"), _this->GetParam<float>("PositionY"), 0.f); //���W
	}

	//��]
	D3DXMatrixRotationZ(&rot, D3DXToRadian(_this->GetParam<float>("Angle")));

	//�s���H�b�g
	world._41 -= _this->GetParam<float>("SizeX") * .5f;
	world._42 -= _this->GetParam<float>("SizeY") * .5f;

	//�s��v�Z
	world = world * scale * rot * pos;

	//�x�[�X�e�N�X�`���̃T�C�Y�擾
	float sizeX = Texture::GetSize().x;
	float sizeY = Texture::GetSize().y;

	//�e�N�X�`���T�C�Y��UV�ϊ�
	float SizeU = _this->GetParam<float>("SizeX") / sizeX;
	float SizeV = _this->GetParam<float>("SizeY") / sizeY;

	//�J�����Ƃ̐F�̍���
	D3DXCOLOR newColor = {};
	D3DXCOLOR thisColor = D3DXCOLOR
	(
		_this->GetParam<float>("ColorR"),
		_this->GetParam<float>("ColorG"),
		_this->GetParam<float>("ColorB"),
		_this->GetParam<float>("ColorA")
	);
	D3DXColorModulate(&newColor, &Camera::Color(), &thisColor);

	// �V�F�[�_
	DirectX::Instance()->pEffect->BeginPass(_this->GetParam<int>("Shader"));

	DirectX::Instance()->pEffect->SetMatrix("world", &world);
	DirectX::Instance()->pEffect->SetMatrix("proj", &DirectX::Instance()->Proj);
	DirectX::Instance()->pEffect->SetFloat("uv_left",
		_this->GetParam<float>("StartU") +
		_this->GetParam<float>("ScrollX") +
		(SizeU / _this->GetParam<float>("DivX"))
		* ((int)_this->GetParam<float>("Pattern") % (int)_this->GetParam<float>("DivX")));
	DirectX::Instance()->pEffect->SetFloat("uv_top",
		_this->GetParam<float>("StartV") +
		_this->GetParam<float>("ScrollY") +
		(SizeV / _this->GetParam<float>("DivY"))
		* ((int)_this->GetParam<float>("Pattern") / (int)_this->GetParam<float>("DivX")));
	DirectX::Instance()->pEffect->SetFloat("uv_width", SizeU / _this->GetParam<float>("DivX"));
	DirectX::Instance()->pEffect->SetFloat("uv_height", SizeV / _this->GetParam<float>("DivY"));
	DirectX::Instance()->pEffect->SetFloat("alpha", newColor.a);
	DirectX::Instance()->pEffect->SetFloat("red", newColor.r);
	DirectX::Instance()->pEffect->SetFloat("green", newColor.g);
	DirectX::Instance()->pEffect->SetFloat("blue", newColor.b);
	DirectX::Instance()->pEffect->SetFloat("scaleX", _this->GetParam<float>("ScaleX"));
	DirectX::Instance()->pEffect->SetFloat("scaleY", _this->GetParam<float>("ScaleY"));
	DirectX::Instance()->pEffect->CommitChanges();
	DirectX::Instance()->pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	DirectX::Instance()->pEffect->EndPass();
};