#include "InGameScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Objects/Player/Player.h"
#include "../../Utility/Collision.h"
#include "../../Utility/ScoreManager.h"
#include "../../Objects/Enemy/Enemy.h"
#include"../../Objects/Effect/Sord.h"
//#include "../Object/Enemy/Nokonoko.h"
#include "../../Objects/Furniture/Floor.h"
#include "../../Objects/Furniture/Table.h"
#include <fstream>

//#define D_LEFT_LAINE		(110)
//#define D_MID_LAINE			(320)
//#define D_RIGHT_LAINE		(530)

#define MAX_LOAD_LINE	(20)
#define MAX_LOAD_COLUMN	(15)
//#define DEBUG_MODE		(0)

void InGameScene::Initialize()
{
	ScoreManager::GetInstance().ResetScore();

	ResourceManager* rm = ResourceManager::GetInstance();

	//GameObjectManager�̃C���X�^���X�擾
	objm = GameObjectManager::GetInstance();
	player = objm->CreateGameObject<Player>(Vector2D(320, 400));		//�v���C���[�|�C���^�̎擾
	//enemy = objm->CreateGameObject<Enemy>(Vector2D(50, 50));			//�v���C���[�|�C���^�̎擾		

	enemy_count[0] = 0;
	enemy_count[1] = 0;
	enemy_count[2] = 0;

	start_flg = true;

	DrawBackGroundCSV();

	//LoadStageMapCSV();

	//SE��ǂݍ���
	mainbgm = rm->GetSoundResource("Resource/Sounds/BGM/mainbgm.mp3");
	ChangeVolumeSoundMem(100, mainbgm);
	PlaySoundMem(mainbgm, DX_PLAYTYPE_LOOP);
}

eSceneType InGameScene::Update(float delta_second)
{
	InputManager* input = InputManager::GetInstance();

	//pause_flg��false�ł���΍X�V����������
	if (!start_flg)
	{
		//�����蔻�菈��
		objm->HitCheck();

		//���[����5�l�ȏ㗭�܂�ƃQ�[���I�[�o�[
		if (enemy_count[0] > 5 || enemy_count[1] > 5 || enemy_count[2] > 5)
		{
			return eSceneType::eResult;
		}

		// �^�C�}�[�X�V����
		time_counter += delta_second;  // �t���[�����ƂɌo�ߎ��Ԃ����Z

		if (time_counter >= 1.0f)  // 1�b�o�߂����ꍇ
		{
			enemy_timer += 1;  // 1�b���炷
			time_counter = 0.0f;  // �J�E���^�[�����Z�b�g
		}

		//2�b�o�߂�����G�𐶐�����
		if (enemy_timer > 0)
		{
			int random = GetRand(2);

			//�ǂ��̃��[���ɐ������邩�������_���Ō��߂�
			switch (random)
			{
			case 0:		//���̃��[��
				enemy = objm->CreateGameObject<Enemy>(Vector2D(D_LEFT_LEAN, 10));
				enemy->SetLane(eLEFT);
				game_enemy_list.push_back(enemy);
				enemy_count[0]++;
				break;

			case 1:		//�^�񒆂̃��[��
				enemy = objm->CreateGameObject<Enemy>(Vector2D(D_MID_LEAN, 10));
				enemy->SetLane(eMID);
				game_enemy_list.push_back(enemy);
				enemy_count[1]++;
				break;

			case 2:		//�E�̃��[��
				enemy = objm->CreateGameObject<Enemy>(Vector2D(D_RIGHT_LEAN, 10));
				enemy->SetLane(eRIGHT);
				game_enemy_list.push_back(enemy);
				enemy_count[2]++;
				break;
			default:
				break;
			}

			enemy_timer = 0;
		}

		//�������[���ɂ��邩�ǂ����̃`�F�b�N����
		testCheckLane();


		__super::Update(delta_second);

		//game_enemy_lisit�̍폜����
		for (int i = 0; i < game_enemy_list.size(); i++)
		{
			//�G�l�~�[�̍폜�t���O��true��������폜����
			if (game_enemy_list[i]->GetDeleteFlag())
			{
				//�����G�̃��[�������擾
				eNowLane lane = game_enemy_list[i]->GetCollision().now_lane;

				//�Ή����郌�[���ɂ���G�̐������炷
				switch (lane)
				{
				case eLEFT:
					enemy_count[0]--;
					break;

				case eMID:
					enemy_count[1]--;
					break;

				case eRIGHT:
					enemy_count[2]--;
					break;

				default:
					break;
				}

				game_enemy_list.erase(game_enemy_list.begin() + i);

				//������x���������s����
				continue;
			}
		}

		//�I�u�W�F�N�g�폜����
		objm->CheckDstroyObject();
	}
	else
	{
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
			start_flg = !start_flg;
		}
	}

	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	__super::Draw();

	ScoreManager::GetInstance().DrawCount();

	//�X�^�[�g���ԕ\��
	if (start_flg)
	{
		//3�C2�C1�̃J�E���g
		if (time_remaining >= 2)
		{
			DrawFormatString(100, 100, GetColor(255, 255, 255), "test_time:%d", time_remaining - 1);
		}
		else if (time_remaining <= 1)		//START�̕\��
		{
			DrawFormatString(100, 100, GetColor(255, 255, 255), "START!!");
		}
	}
}

void InGameScene::Finalize()
{
	player = nullptr;

	// �I�u�W�F�N�g���X�g����Ȃ珈�����I������
	if (game_enemy_list.empty())
	{
		return;
	}
	// �I�u�W�F�N�g���X�g���̃I�u�W�F�N�g���폜����
	//for (GameObject* obj : game_enemy_list)
	//{
	//	delete obj;
	//}

	// ���I�z��̉��
	game_enemy_list.clear();
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
		// ���o����������0�Ȃ珰�i�w�i�j�𐶐�����
		if (c == '0')
		{
			objm->CreateGameObject<Floor>(generate_location);
			x++;
		}
		//���o����������1�Ȃ�e�[�u���𐶐�����
		else if (c == '1')
		{
			objm->CreateGameObject<Table>(generate_location);
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

//�v���C���[�Ƃ��Ȃ����[���ɂ��邩�ǂ���
void InGameScene::testCheckLane()
{
	for (int i = 0; i < game_enemy_list.size(); i++)
	{

		if (game_enemy_list[i]->GetCollision().now_lane == player->GetCollision().now_lane)
		{
			game_enemy_list[i]->CheckLane(true);
		}
		else
		{
			game_enemy_list[i]->CheckLane(false);
		}
	}

	//���X�g�̕�����for������
	//for (int i = 0; i < game_enemy_list.size(); i++)
	//{
	//	

	//	//�������[�����ǂ����̔���𑗂�
	//	if (game_enemy_list[i]->GetCollision().now_lane == player->GetCollision().now_lane)
	//	{
	//		game_enemy_list[i]->CheckLane(true);
	//	}
	//	else
	//	{
	//		game_enemy_list[i]->CheckLane(false);
	//	}
	//}
}

//void InGameScene::DrawBackGroundCSV() const
//{
//
//	FILE* fp = NULL;
//
//	std::string file_name = "Resource/Map/Mapdate.csv";
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
//	Floor* floor = nullptr;
//
//	// �t�@�C�����̕������m�F���Ă���
//	while (true)
//	{
//		//�`��ʒu�ݒ�
//		//Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
//
//		// �t�@�C������1�������o����
//		int c = fgetc(fp);
//
//		// ���o����������EOF�Ȃ烋�[�v�I��
//		if (c == EOF)
//		{
//			break;
//		}
//		// ���o����������0�Ȃ珰�i�w�i�j�𐶐�����
//		if (c == '0')	
//		{
//			stage_data[x][y] = 0;
//			x++;
//		}
//		//���o����������1�Ȃ�e�[�u���𐶐�����
//		else if (c == '1')
//		{
//			objm->CreateGameObject<Table>(generate_location);
//			x++;
//		}
//		//���o�����������h�b�g�Ȃ牽�����������A���̕���������
//		else if (c == '.')
//		{
//			x++;
//		}
//		// ���o�������������s�����Ȃ�A���̍s�����ɍs��
//		else if (c == '\n')
//		{
//			x = 0;
//			y++;
//		}
//	}
//
//	// �J�����t�@�C�������
//	fclose(fp);
//}

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