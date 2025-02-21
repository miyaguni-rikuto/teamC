#include "InGameScene.h"
//#include "../../Objects/Player/Player.h"
//#include "../../Objects/Enemy/EnemyBase.h"
//#include "../../Objects/Enemy/Kuribo.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
//#include "../../Objects/Block/BrickBlock.h"
//#include "../../Objects/Block/Block.h"
//#include "../../Objects/Block/Hatena.h"
//#include "../../Objects/Block/ClayPipe.h"
#include "DxLib.h"
#include <fstream>

InGameScene::InGameScene()
/*: player(nullptr)
, enemy(nullptr)*/
	: back_ground_image(NULL)
	, back_ground_sound(NULL)
	, e_count(0)
	, pause_flag(false)
	, location(0.0f, 0.0f)
{

}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	////�X�e�[�W�̓ǂݍ���
	//LoadStageMapCSV();

	////�J�������W�̐ݒ�
	////screen_origin_position.x = (640 / 2);
	////screen_origin_position.y = (480 / 2);

	////screen_offest�͕`�悾����ς��Ă��邩����ۂ�location�͕ς��Ȃ��͂�
	//player = CreateObject<Player>(Vector2D(100.0f, 60.0f));

	//CreateObject<Kuribo>(Vector2D(200.f, 400.0f));

	//// �X�N���[���I�t�Z�b�g��ݒ�
	////screen_offset.y = D_OBJECT_SIZE * 3.0f;
	//screen_offset.x = 0.0f;
	//camera_x = 0.0f;
	////screen_offset.x = player->GetLocation().x - (640 / 2);

	////// �w�i�摜�̓ǂݍ���
	//ResourceManager* rm = ResourceManager::CreateInstance();
	//back_ground_image = rm->GetImages("Resource/Images/�z�u�f��/NES---Super-Mario-Bros---World-1-1�i�C���Łj.png")[0];
	////// BGM�̓ǂݍ���
	////back_ground_sound = rm->GetSounds("Resource/Sounds/start-music.mp3");

	////PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK);
}

//���͏���
eSceneType InGameScene::Update(const float& delta_second)
{
	////���͏��̎擾
	//InputManager* input = InputManager::CreateInstance();

	////�v���C���[���^�񒆂��E���ɂ�����
	//if (player->GetLocation().x > 320 + camera_x)
	//{
	//	//��ʂ̐^�� - �v���C���[�̍��W = �E���ɂǂꂾ������Ă��邩
	//	camera_x = player->GetLocation().x - 320;
	//	//���l���X�N���[���I�t�Z�b�g�ɑ��
	//	screen_offset.x = -(camera_x);
	//}

	////�v���C���[����ʍ����ɍs���Ȃ��悤�ɂ��鏈��
	//if (player->GetLocation().x < screen_offset.x * -1)
	//{
	//	//player�̍��W
	//	Vector2D player_loc;
	//	player_loc.x = abs(screen_offset.x) + 0.01f;		//���W���J�������W�̍��[�ɐݒ�
	//	player_loc.y = player->GetLocation().y;				//y���W��ς����ɑ��
	//	player->SetLocation(player_loc);
	//	player->velocity.x = 0.0f;
	//}

	////PAUSE��ʂւ̑J��
	//if (input->GetKeyDown(KEY_INPUT_P) || input->GetButtonDown(XINPUT_BUTTON_START))
	//{
	//	pause_flag = !pause_flag;
	//}

	////PAUSE��ʂł͂Ȃ����
	//if (!pause_flag)
	//{
	//	// �e�N���X�̍X�V�������Ăяo��
	//	__super::Update(delta_second);

	//	//// �v���C���[�����񂾂�A�ăX�^�[�g
	//	//if (player->GetDestroy())
	//	//{
	//	//	return eSceneType::re_start;
	//	//}
	//}

	///*if (screen_offset.x > END_POINT)
	//{
	//	if((player->GetLocation().x / 2) > )
	//	screen_offset.x -= 0.1f;
	//}*/

	//if (abs(player->GetLocation().x) > 640 / 2)
	//{
	//	//screen_offset.x += 0.01f;
	//}

	// �V�[������ԋp����
	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	// �w�i�摜�̕`��
	//DrawRotaGraph(0, 480, 2.0, 0.0, back_ground_image, TRUE);

	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location.x + screen_offset.x;

	//float center = abs((graph_location.x / 2));
	//float p_loc = abs(player->GetLocation().x);

	//if (player != nullptr)
	//{
	//	if (p_loc > center)
	//	{
	//		
	//	}
	//}

	//DrawGraphF(0, 480, back_ground_image, TRUE);

	//DrawFormatString(0, 90, GetColor(255, 255, 255), "%f", this->location.x);

	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

	DrawString(50, 50, "�Q�[����ʂł�", GetColor(255, 255, 255), TRUE);

	// UI�n�̕`�揈��
	if (pause_flag)
	{
		DrawString(10, 10, " P A U S E ", GetColor(255, 255, 255), TRUE);
	}
}

void InGameScene::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::in_game;
}

/// <summary>
/// �����蔻��m�F����
/// </summary>
/// <param name="target">1�ڂ̃Q�[���I�u�W�F�N�g</param>
/// <param name="partner">2�ڂ̃Q�[���I�u�W�F�N�g</param>
void InGameScene::HitCheckObject(GameObject* target, GameObject* partner)
{
	// �k���|�`�F�b�N
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	// �����蔻������擾
	Collision tc = target->GetCollision();
	Collision pc = partner->GetCollision();

	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{

		// �����̎n�_�ƏI�_��ݒ肷��
		tc.box_location[0] = target->GetLocation();
		pc.box_location[0] = partner->GetLocation();

		// ��`���m�̓����蔻��
		if (IsCheckCollision(tc, pc))
		{
			// �������Ă��邱�Ƃ�ʒm����
			target->OnHitCollision(partner);
			partner->OnHitCollision(target);
		}

	}

}

/// <summary>
/// �X�e�[�W�}�b�v�i�ǁj�ǂݍ��ݏ���
/// </summary>
void InGameScene::LoadStageMapCSV()
{
	//FILE* fp = NULL;
	//std::string file_name = "Resource/Maps/Book1.csv";

	//// �w�肳�ꂽ�t�@�C�����J��
	//errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	//// �G���[�`�F�b�N
	//if (result != 0)
	//{
	//	throw (file_name + "���J���܂���");
	//}

	//int x = 0;
	//int y = 0;

	//// �t�@�C�����̕������m�F���Ă���
	//while (true)
	//{
	//	// �t�@�C������1�������o����
	//	int c = fgetc(fp);

	//	// ���o����������EOF�Ȃ烋�[�v�I��
	//	if (c == EOF)
	//	{
	//		break;
	//	}
	//	// ���o����������G�Ȃ�A���𐶐�
	//	else if (c == '1')
	//	{
	//		Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);

	//		CreateObject<BrickBlock>(generate_location);
	//		x++;
	//	}
	//	// ���o����������B�Ȃ�A�󂹂�u���b�N�𐶐�
	//	else if (c == 'B')
	//	{
	//		Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
	//		CreateObject<Block>(generate_location);
	//		x++;
	//	}
	//	// ���o�����������n�e�i�Ȃ�A�n�e�i�u���b�N�𐶐�
	//	else if (c == '?')
	//	{
	//		Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
	//		CreateObject<Hatena>(generate_location);
	//		x++;
	//	}
	//	//���o����������D�Ȃ�A�y�ǂ𐶐�
	//	else if (c == 'D')
	//	{
	//		// �t�@�C������1�������o����
	//		int b = fgetc(fp);

	//		//D�̎��̕�����1�`4�̕�����������Ή������摜��ݒ肵����
	//		if (b == '1')
	//		{
	//			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
	//			CreateObject<ClayPipe>(generate_location)->SetImage(0);
	//		}
	//		else if (b == '2')
	//		{
	//			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
	//			CreateObject<ClayPipe>(generate_location)->SetImage(1);
	//		}
	//		else if (b == '3')
	//		{
	//			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
	//			CreateObject<ClayPipe>(generate_location)->SetImage(2);
	//		}
	//		else if (b == '4')
	//		{
	//			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
	//			CreateObject<ClayPipe>(generate_location)->SetImage(3);
	//		}

	//		x++;
	//	}
	//	// ���o�����������󔒕����Ȃ�A�������Ȃ��Ŏ��̕��������ɍs��
	//	else if (c == '0')
	//	{
	//		x++;
	//	}
	//	// ���o�������������s�����Ȃ�A���̍s�����ɍs��
	//	else if (c == '\n')
	//	{
	//		x = 0;
	//		y++;
	//	}

	//}

	//// �J�����t�@�C�������
	//fclose(fp);
}