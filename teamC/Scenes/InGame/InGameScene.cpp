#include "InGameScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Objects/Player/Player.h"
#include "../../Utility/Collision.h"
#include "../../Objects/Enemy/Enemy.h"
//#include "../Object/Enemy/Nokonoko.h"
#include "../../Objects/Furniture/Floor.h"
#include "../../Objects/Furniture/Table.h"
#include <fstream>

#define D_LEFT_LAINE		(110)
#define D_MID_LAINE			(320)
#define D_RIGHT_LAINE		(530)

#define MAX_LOAD_LINE	(20)
#define MAX_LOAD_COLUMN	(15)
//#define DEBUG_MODE		(0)

void InGameScene::Initialize()
{
	objm = GameObjectManager::GetInstance();
	player = objm->CreateGameObject<Player>(Vector2D(320, 400));
	enemy = objm->CreateGameObject<Enemy>(Vector2D(50, 50));

	start_flg = true;

	DrawBackGroundCSV();

	//LoadStageMapCSV();
}

eSceneType InGameScene::Update(float delta_second)
{
	InputManager* input = InputManager::GetInstance();

	//エネミーの生成
	for (int i = 0; i <= 3; i++)
	{
		Enemy_count[i]++;
	}
	if (Enemy_count[0] >= 150)
	{
		Enemy_count[0] = 0;
		if (GetRand(1) == 1)
		{
			objm->CreateGameObject<Enemy>(Vector2D(100, 10));
		}
		else
			objm->CreateGameObject<Enemy>(Vector2D(100, 10));
	}

	if (Enemy_count[1] >= 350)
	{
		Enemy_count[1] = 1;
		if (GetRand(1) == 1)
		{
			objm->CreateGameObject<Enemy>(Vector2D(250, 10));
		}
		else
			objm->CreateGameObject<Enemy>(Vector2D(250, 10));
	}

	if (Enemy_count[2] >= 500)
	{
		Enemy_count[2] = 2;
		if (GetRand(1) == 1)
		{
			objm->CreateGameObject<Enemy>(Vector2D(400, 10));
		}
		else
			objm->CreateGameObject<Enemy>(Vector2D(400, 10));
	}

#ifndef DEBUG_MODE

	objm->HitCheck();

	__super::Update(delta_second);

	//DeleteObject();

	Draw();

	//Dキーが押された場合
	if (input->GetKeyState(KEY_INPUT_D) == eInputState::Pressed)
	{
		return eSceneType::eResult;
	}

#else
	//pause_flgがfalseであれば更新処理を入れる
	if (!start_flg)
	{
		objm->HitCheck();

		__super::Update(delta_second);

		//Dキーが押された場合
		if (input->GetKeyState(KEY_INPUT_D) == eInputState::Pressed)
		{
			return eSceneType::eResult;
		}

		//DeleteObject();
	}
	else
	{
		// タイマー更新処理
		time_counter += delta_second;  // フレームごとに経過時間を加算

		if (time_counter >= 1.0f)  // 1秒経過した場合
		{
			time_remaining -= 1;  // 1秒減らす
			time_counter = 0.0f;  // カウンターをリセット
		}

		// 残り時間が0になったら、必要な処理を追加
		if (time_remaining <= 0)
		{
			time_remaining = 0;
			start_flg = !start_flg;

			// ゲームオーバーや別の処理を追加することも可能
		}
	}

#endif // DEBUG	
	Draw();

	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	__super::Draw();

	//スタート時間表示
	if (start_flg)
	{
		if (time_remaining >= 2)
		{
			DrawFormatString(100, 100, GetColor(255, 255, 255), "test_time:%d", time_remaining - 1);
		}
		else if (time_remaining <= 1)
		{
			DrawFormatString(100, 100, GetColor(255, 255, 255), "START!!");
		}
	}
}

void InGameScene::Finalize()
{
	player = nullptr;
	enemy = nullptr;
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
//	// 指定されたファイルを開く
//	errno_t result = fopen_s(&fp, file_name.c_str(), "r");
//
//	// エラーチェック
//	if (result != 0)
//	{
//		throw (file_name + "が開けません");
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
//	// ファイル内の文字を確認していく
//	while (true)
//	{
//
//		// ファイルから1文字抽出する
//		int c = fgetc(fp);
//
//		//オブジェクトを生成する位置
//		Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
//
//		// 抽出した文字がEOFならループ終了
//		if (c == EOF)
//		{
//			break;
//		}
//		//抽出した文字が'P'ならPlayerを描画する
//		else if (c == 'M')
//		{
//			p = objm->CreateGameObject<Player>(generate_location);
//			camera->Set_Player(p);
//			p->Set_Camera(camera);
//
//			x++;
//		}
//		// 抽出した文字がGなら、地面を生成
//		else if (c == 'G')
//		{
//			ground = objm->CreateGameObject<Ground>(generate_location);
//			ground->Set_Camera(camera);
//			x++;
//		}
//		//抽出した文字がKなら、クリボー（敵）を生成する
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
//		//抽出した文字が0なら何も生成せず、次の文字を見る
//		else if (c == '0')
//		{
//			x++;
//		}
//		// 抽出した文字が改行文字なら、次の行を見に行く
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
//	// 開いたファイルを閉じる
//	fclose(fp);
//}

void InGameScene::DrawBackGroundCSV() const
{

	FILE* fp = NULL;

	std::string file_name = "Resource/Map/Mapdate.csv";

	// 指定されたファイルを開く
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// エラーチェック
	if (result != 0)
	{
		throw (file_name + "が開けません");
	}

	int x = 0;
	int y = 0;
	Floor* floor = nullptr;

	// ファイル内の文字を確認していく
	while (true)
	{
		//描画位置設定
		Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);

		// ファイルから1文字抽出する
		int c = fgetc(fp);

		// 抽出した文字がEOFならループ終了
		if (c == EOF)
		{
			break;
		}
		// 抽出した文字が0なら床（背景）を生成する
		if (c == '0')
		{
			objm->CreateGameObject<Floor>(generate_location);
			x++;
		}
		//抽出した文字が1ならテーブルを生成する
		else if (c == '1')
		{
			objm->CreateGameObject<Table>(generate_location);
			x++;
		}
		//抽出した文字がドットなら何も生成せず、次の文字を見る
		else if (c == '.')
		{
			x++;
		}
		// 抽出した文字が改行文字なら、次の行を見に行く
		else if (c == '\n')
		{
			x = 0;
			y++;
		}
	}

	// 開いたファイルを閉じる
	fclose(fp);
}

//なじレーンにいるかどうか
//bool InGameScene::testCheckLane(Player* player, Enemy* enemy)
//{
//	if (enemy->GetCollision().now_lane == player->GetCollision().now_lane)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

//void InGameScene::DrawBackGroundCSV() const
//{
//
//	FILE* fp = NULL;
//
//	std::string file_name = "Resource/Map/Mapdate.csv";
//
//	// 指定されたファイルを開く
//	errno_t result = fopen_s(&fp, file_name.c_str(), "r");
//
//	// エラーチェック
//	if (result != 0)
//	{
//		throw (file_name + "が開けません");
//	}
//
//	int x = 0;
//	int y = 0;
//	Floor* floor = nullptr;
//
//	// ファイル内の文字を確認していく
//	while (true)
//	{
//		//描画位置設定
//		//Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
//
//		// ファイルから1文字抽出する
//		int c = fgetc(fp);
//
//		// 抽出した文字がEOFならループ終了
//		if (c == EOF)
//		{
//			break;
//		}
//		// 抽出した文字が0なら床（背景）を生成する
//		if (c == '0')	
//		{
//			stage_data[x][y] = 0;
//			x++;
//		}
//		//抽出した文字が1ならテーブルを生成する
//		else if (c == '1')
//		{
//			objm->CreateGameObject<Table>(generate_location);
//			x++;
//		}
//		//抽出した文字がドットなら何も生成せず、次の文字を見る
//		else if (c == '.')
//		{
//			x++;
//		}
//		// 抽出した文字が改行文字なら、次の行を見に行く
//		else if (c == '\n')
//		{
//			x = 0;
//			y++;
//		}
//	}
//
//	// 開いたファイルを閉じる
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