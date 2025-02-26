#include "Sord.h"
#include "../../Objects/GameObject.h"
#include "../../Objects/GameObjectManager.h"
#include"../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"

Sord::Sord() :
	hit_point(3)
{
}

Sord::~Sord()
{
}

void Sord::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImageResource("Resource/Images/Item//Sord.png")[0];

	collision.object_type = eObjectType::eSord;

	z_layer = 4;

}

void Sord::Update(float delta_second)
{
	InputManager *input = InputManager::GetInstance();

	//ƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚½‚çHP‚ðí‚é
	if (input->GetButtonState(XINPUT_BUTTON_A) == Pressed)
	{
		hit_point--;
	}

	//HP‚ª0‚É‚È‚Á‚½‚çÁ‚·
	if (hit_point == 0)
	{
		GameObjectManager* obm = GameObjectManager::GetInstance();
		obm->DestroyGameObject(this);
	}
}

void Sord::Draw(const Vector2D& screen_offset) const
{
	Vector2D graph_location = this->location - screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 1.4, image, TRUE, filp_flag);
}

void Sord::Finalize()
{
}

void Sord::OnHitCollision(GameObject* target)
{
	
}
