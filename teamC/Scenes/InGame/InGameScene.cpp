#include "InGameScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
//#include "../Object/Player/Player.h"
#include "../../Utility/Collision.h"
//#include "../Object/Enemy/Kuribo.h"
//#include "../Object/Enemy/Nokonoko.h"
#include "../../Objects/Floor/Floor.h"
#include <fstream>

#define MAX_LOAD_LINE	20;
#define MAX_LOAD_COLUMN	(15);

void InGameScene::Initialize()
{
	objm = GameObjectManager::GetInstance();

	//LoadStageMapCSV();
}

eSceneType InGameScene::Update(float delta_second)
{
	objm->HitCheck();

	InputManager* input = InputManager::GetInstance();

	/*if (p->Get_DeathCount() >= 1)
	{
		return eSceneType::eResult;
	}*/

	// �^�C�}�[�X�V����
	time_counter += delta_second;  // �t���[�����ƂɌo�ߎ��Ԃ����Z

	if (time_counter >= 1.0f)  // 1�b�o�߂����ꍇ
	{
		time_remaining -= 1;  // 1�b���炷
		time_counter = 0.0f;  // �J�E���^�[�����Z�b�g
	}

	// �c�莞�Ԃ�0�ɂȂ�����A�K�v�ȏ�����ǉ�
	if (time_remaining <= 0)
	{
		time_remaining = 0;
		// �Q�[���I�[�o�[��ʂ̏�����ǉ����邱�Ƃ��\
	}

	__super::Update(delta_second);

	//DeleteObject();

	Draw();

	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	DrawBackGroundCSV();

	__super::Draw();
}

void InGameScene::Finalize()
{

}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}

void InGameScene::CheckCollision(GameObject* target, GameObject* partner)
{
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	Collision tc = target->GetCollision();
	Collision pc = partner->GetCollision();

	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{
		tc.pivot += target->GetLocation();
		pc.pivot += partner->GetLocation();

		if (tc.IsCheckHitCollision(tc, pc))
		{
			target->OnHitCollision(partner);
			partner->OnHitCollision(target);
		}
	}

}

//void InGameScene::LoadStageMapCSV()
//{
//
//	FILE* fp = NULL;
//
//	std::string file_name = "Resource/Map/Stage_Object.csv";
//
//
//	// �w�肳�ꂽ�t�@�C�����J��
//	errno_t result = fopen_s(&fp, file_name.c_str(), "r");
//
//	// �G���[�`�F�b�N
//	if (result != 0)
//	{
//		throw (file_name + "���J���܂���");
//	}
//
//	int x = 0;
//	int y = 0;
//	Ground* ground = nullptr;
//	Cloud* cloud = nullptr;
//	Kuribo* k = nullptr;
//	Nokonoko* n = nullptr;
//	Pipe* pipe = nullptr;
//	GoalFlag* f = nullptr;
//
//	// �t�@�C�����̕������m�F���Ă���
//	while (true)
//	{
//
//		// �t�@�C������1�������o����
//		int c = fgetc(fp);
//
//		//�I�u�W�F�N�g�𐶐�����ʒu
//		Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
//
//		// ���o����������EOF�Ȃ烋�[�v�I��
//		if (c == EOF)
//		{
//			break;
//		}
//		//���o����������'P'�Ȃ�Player��`�悷��
//		else if (c == 'M')
//		{
//			p = objm->CreateGameObject<Player>(generate_location);
//			camera->Set_Player(p);
//			p->Set_Camera(camera);
//
//			x++;
//		}
//		// ���o����������G�Ȃ�A�n�ʂ𐶐�
//		else if (c == 'G')
//		{
//			ground = objm->CreateGameObject<Ground>(generate_location);
//			ground->Set_Camera(camera);
//			x++;
//		}
//		//���o����������K�Ȃ�A�N���{�[�i�G�j�𐶐�����
//		else if (c == 'C')
//		{
//			k = objm->CreateGameObject<Kuribo>(generate_location);
//			k->Set_Camera(camera);
//			x++;
//		}
//		else if (c == 'N')
//		{
//			n = objm->CreateGameObject<Nokonoko>(generate_location);
//			n->Set_Camera(camera);
//			x++;
//		}
//		else if (c == 'B')
//		{
//			c = fgetc(fp);
//			switch (c)
//			{
//			case '?':
//				c = fgetc(fp);
//				switch (c)
//				{
//				case 'M':
//					objm->CreateGameObject<Question>(generate_location)->SetItemType(eMushroom);
//					x++;
//					break;
//
//				case 'F':
//					objm->CreateGameObject<Question>(generate_location)->SetItemType(eFlower);
//					x++;
//					break;
//
//				case 'C':
//					objm->CreateGameObject<Question>(generate_location)->SetItemType(eCoin);
//					x++;
//					break;
//
//				case 'S':
//					objm->CreateGameObject<Question>(generate_location)->SetItemType(eStar);
//					x++;
//					break;
//
//				case 'O':
//					objm->CreateGameObject<Question>(generate_location)->SetItemType(eOneup);
//					x++;
//					break;
//
//				default:
//					objm->CreateGameObject<Question>(generate_location)->SetItemType(eCoin);
//					x++;
//					break;
//				}
//
//				break;
//
//			case '0':
//				objm->CreateGameObject<Brick>(generate_location);
//				x++;
//				break;
//
//			case '1':
//				objm->CreateGameObject<HardBlock>(generate_location);
//				x++;
//				break;
//
//			case 'H':
//				x++;
//				break;
//			}
//		}
//		else if (c == 'P')
//		{
//			c = fgetc(fp);
//
//			switch (c)
//			{
//			case '0':
//				pipe = objm->CreateGameObject<Pipe>(generate_location);
//				pipe->Set_Image(0);
//				x++;
//				break;
//
//			case '1':
//				pipe = objm->CreateGameObject<Pipe>(generate_location);
//				pipe->Set_Image(1);
//				x++;
//				break;
//
//			case '2':
//				pipe = objm->CreateGameObject<Pipe>(generate_location);
//				pipe->Set_Image(2);
//				x++;
//				break;
//
//			case '3':
//				pipe = objm->CreateGameObject<Pipe>(generate_location);
//				pipe->Set_Image(3);
//				x++;
//				break;
//			case 'E':
//
//				objm->CreateGameObject<Pipeenter>(Vector2D((generate_location.x + 16.0f), generate_location.y + 8.0f));
//				x++;
//				break;
//			}
//		}
//		else if (c == 'F')
//		{
//			c = fgetc(fp);
//			switch (c)
//			{
//			case '0':
//				f = objm->CreateGameObject<GoalFlag>(generate_location);
//				f->Set_Image(0);
//				x++;
//				break;
//
//			case '1':
//				f = objm->CreateGameObject<GoalFlag>(generate_location);
//				f->Set_Image(1);
//				x++;
//				break;
//			}
//		}
//		//���o����������0�Ȃ牽�����������A���̕���������
//		else if (c == '0')
//		{
//			x++;
//		}
//		// ���o�������������s�����Ȃ�A���̍s�����ɍs��
//		else if (c == '\n')
//		{
//			x = 0;
//			y++;
//		}
//
//
//
//	}
//
//	// �J�����t�@�C�������
//	fclose(fp);
//}

void InGameScene::DrawBackGroundCSV() const
{

	FILE* fp = NULL;

	std::string file_name = "Resource/Map/Mapdate.csv";

	// �w�肳�ꂽ�t�@�C�����J��
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw (file_name + "���J���܂���");
	}

	int x = 0;
	int y = 0;
	Floor* floor = nullptr;

	// �t�@�C�����̕������m�F���Ă���
	while (true)
	{
		//�`��ʒu�ݒ�
		Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);

		// �t�@�C������1�������o����
		int c = fgetc(fp);

		// ���o����������EOF�Ȃ烋�[�v�I��
		if (c == EOF)
		{
			break;
		}
		// ���o����������1�Ȃ珰�i�w�i�j�𐶐�����
		if (c == '1')
		{
			objm->CreateGameObject<Floor>(generate_location);
			x++;
		}
		//���o�����������h�b�g�Ȃ牽�����������A���̕���������
		else if (c == '.')
		{
			x++;
		}
		// ���o�������������s�����Ȃ�A���̍s�����ɍs��
		else if (c == '\n')
		{
			x = 0;
			y++;
		}
	}

	// �J�����t�@�C�������
	fclose(fp);
}

//void InGameScene::DeleteObject()
//{
//	std::vector<GameObject*> object_list = objm->GetObjectsList();
//
//	if (!object_list.empty())
//	{
//		for (int i = 0; i < object_list.size(); i++)
//		{
//			int x = (object_list[i]->GetLocation().x + OBJECT_SIZE / 2) - offset;
//			if (0 >= x)
//			{
//				objm->DestroyGameObject(object_list[i]);
//
//			}
//		}
//
//	}
//}