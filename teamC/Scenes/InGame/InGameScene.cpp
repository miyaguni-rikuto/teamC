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

	//GameObjectManagerのインスタンス取得
	objm = GameObjectManager::GetInstance();
	player = objm->CreateGameObject<Player>(Vector2D(320, 400));		//プレイヤーポインタの取得
	//enemy = objm->CreateGameObject<Enemy>(Vector2D(50, 50));			//プレイヤーポインタの取得		

	enemy_count[0] = 0;
	enemy_count[1] = 0;
	enemy_count[2] = 0;

	start_flg = true;

	DrawBackGroundCSV();

	//LoadStageMapCSV();

	//SEを読み込む
	mainbgm = rm->GetSoundResource("Resource/Sounds/BGM/mainbgm.mp3");
	ChangeVolumeSoundMem(100, mainbgm);
	PlaySoundMem(mainbgm, DX_PLAYTYPE_LOOP);
}

eSceneType InGameScene::Update(float delta_second)
{
	InputManager* input = InputManager::GetInstance();

	//pause_flgがfalseであれば更新処理を入れる
	if (!start_flg)
	{
		//当たり判定処理
		objm->HitCheck();

		//レーンに5人以上溜まるとゲームオーバー
		if (enemy_count[0] > 5 || enemy_count[1] > 5 || enemy_count[2] > 5)
		{
			return eSceneType::eResult;
		}

		// タイマー更新処理
		time_counter += delta_second;  // フレームごとに経過時間を加算

		if (time_counter >= 1.0f)  // 1秒経過した場合
		{
			enemy_timer += 1;  // 1秒減らす
			time_counter = 0.0f;  // カウンターをリセット
		}

		//2秒経過したら敵を生成する
		if (enemy_timer > 0)
		{
			int random = GetRand(2);

			//どこのレーンに生成するかをランダムで決める
			switch (random)
			{
			case 0:		//左のレーン
				enemy = objm->CreateGameObject<Enemy>(Vector2D(D_LEFT_LEAN, 10));
				enemy->SetLane(eLEFT);
				game_enemy_list.push_back(enemy);
				enemy_count[0]++;
				break;

			case 1:		//真ん中のレーン
				enemy = objm->CreateGameObject<Enemy>(Vector2D(D_MID_LEAN, 10));
				enemy->SetLane(eMID);
				game_enemy_list.push_back(enemy);
				enemy_count[1]++;
				break;

			case 2:		//右のレーン
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

		//同じレーンにいるかどうかのチェック処理
		testCheckLane();


		__super::Update(delta_second);

		//game_enemy_lisitの削除処理
		for (int i = 0; i < game_enemy_list.size(); i++)
		{
			//エネミーの削除フラグがtrueだったら削除する
			if (game_enemy_list[i]->GetDeleteFlag())
			{
				//消す敵のレーン情報を取得
				eNowLane lane = game_enemy_list[i]->GetCollision().now_lane;

				//対応するレーンにいる敵の数を減らす
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

				//もう一度処理を実行する
				continue;
			}
		}

		//オブジェクト削除処理
		objm->CheckDstroyObject();
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
		}
	}

	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	__super::Draw();

	ScoreManager::GetInstance().DrawCount();

	//スタート時間表示
	if (start_flg)
	{
		//3，2，1のカウント
		if (time_remaining >= 2)
		{
			DrawFormatString(100, 100, GetColor(255, 255, 255), "test_time:%d", time_remaining - 1);
		}
		else if (time_remaining <= 1)		//STARTの表示
		{
			DrawFormatString(100, 100, GetColor(255, 255, 255), "START!!");
		}
	}
}

void InGameScene::Finalize()
{
	player = nullptr;

	// オブジェクトリストが空なら処理を終了する
	if (game_enemy_list.empty())
	{
		return;
	}
	// オブジェクトリスト内のオブジェクトを削除する
	//for (GameObject* obj : game_enemy_list)
	//{
	//	delete obj;
	//}

	// 動的配列の解放
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

//プレイヤーとおなじレーンにいるかどうか
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

	//リストの分だけfor分を回す
	//for (int i = 0; i < game_enemy_list.size(); i++)
	//{
	//	

	//	//同じレーンかどうかの判定を送る
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