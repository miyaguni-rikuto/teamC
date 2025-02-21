#include "GameObject.h"
#include "../Scenes/SceneBase.h"
#include "DxLib.h"

GameObject::GameObject() :
	owner_scene(nullptr),
	location(0.0f),
	image(NULL),
	z_layer(0),
	mobility(eMobilityType::Stationary)
{

}

GameObject::~GameObject()
{

}

/// <summary>
/// ����������
/// </summary>
void GameObject::Initialize()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void GameObject::Update(float delta_second)
{

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset">�I�t�Z�b�g�l</param>
void GameObject::Draw(const Vector2D& screen_offset) const
{
	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, FALSE, flip_flg);
}

/// <summary>
/// �I��������
/// </summary>
void GameObject::Finalize()
{
	move_animation.clear();
}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void GameObject::OnHitCollision(GameObject* hit_object)
{

}

/// <summary>
/// ���L�V�[�����̐ݒ�
/// </summary>
/// <param name="scene">���L�V�[�����</param>
void GameObject::SetOwnerScene(SceneBase* scene)
{
	this->owner_scene = scene;
}

/// <summary>
/// �ʒu���W�擾����
/// </summary>
/// <returns>�ʒu���W���</returns>
const Vector2D& GameObject::GetLocation() const
{
	return location;
}

/// <summary>
/// �ʒu���ύX����
/// </summary>
/// <param name="location">�ύX�������ʒu���</param>
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

/// <summary>
/// �����蔻��擾����
/// </summary>
/// <returns>�����蔻����</returns>
Collision GameObject::GetCollision() const
{
	return collision;
}

//�e�ӂ̓����蔻����
void GameObject::SetCollision(bool t, bool b, bool l, bool r)
{
	this->collision.hitCheck.H_top = t;
	this->collision.hitCheck.H_bottom = b;
	this->collision.hitCheck.H_left = l;
	this->collision.hitCheck.H_right = r;
}

//�{�b�N�X�T�C�Y�擾����
Vector2D GameObject::GetBoxsize() const
{
	return this->collision.box_size;
}

/// <summary>
/// Z���C���[���擾����
/// </summary>
/// <returns>Z���C���[���</returns>
const int GameObject::GetZLayer() const
{
	return z_layer;
}

/// <summary>
/// �������̎擾����
/// </summary>
/// <returns>�������</returns>
const eMobilityType GameObject::GetMobility() const
{
	return mobility;
}

//�摜���]���
void GameObject::SetFli_flg(int flip_flg)
{
	this->flip_flg = flip_flg;
}

//�A�j���[�V��������
void GameObject::AnimationControl(float delota_second)
{

}