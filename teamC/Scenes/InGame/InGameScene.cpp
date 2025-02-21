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
	////ステージの読み込み
	//LoadStageMapCSV();

	////カメラ座標の設定
	////screen_origin_position.x = (640 / 2);
	////screen_origin_position.y = (480 / 2);

	////screen_offestは描画だけを変えているから実際のlocationは変わらないはず
	//player = CreateObject<Player>(Vector2D(100.0f, 60.0f));

	//CreateObject<Kuribo>(Vector2D(200.f, 400.0f));

	//// スクリーンオフセットを設定
	////screen_offset.y = D_OBJECT_SIZE * 3.0f;
	//screen_offset.x = 0.0f;
	//camera_x = 0.0f;
	////screen_offset.x = player->GetLocation().x - (640 / 2);

	////// 背景画像の読み込み
	//ResourceManager* rm = ResourceManager::CreateInstance();
	//back_ground_image = rm->GetImages("Resource/Images/配置素材/NES---Super-Mario-Bros---World-1-1（修正版）.png")[0];
	////// BGMの読み込み
	////back_ground_sound = rm->GetSounds("Resource/Sounds/start-music.mp3");

	////PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK);
}

//入力処理
eSceneType InGameScene::Update(const float& delta_second)
{
	////入力情報の取得
	//InputManager* input = InputManager::CreateInstance();

	////プレイヤーが真ん中より右側にいたら
	//if (player->GetLocation().x > 320 + camera_x)
	//{
	//	//画面の真ん中 - プレイヤーの座標 = 右側にどれだけずれているか
	//	camera_x = player->GetLocation().x - 320;
	//	//数値をスクリーンオフセットに代入
	//	screen_offset.x = -(camera_x);
	//}

	////プレイヤーが画面左側に行かないようにする処理
	//if (player->GetLocation().x < screen_offset.x * -1)
	//{
	//	//playerの座標
	//	Vector2D player_loc;
	//	player_loc.x = abs(screen_offset.x) + 0.01f;		//座標をカメラ座標の左端に設定
	//	player_loc.y = player->GetLocation().y;				//y座標を変えずに代入
	//	player->SetLocation(player_loc);
	//	player->velocity.x = 0.0f;
	//}

	////PAUSE画面への遷移
	//if (input->GetKeyDown(KEY_INPUT_P) || input->GetButtonDown(XINPUT_BUTTON_START))
	//{
	//	pause_flag = !pause_flag;
	//}

	////PAUSE画面ではなければ
	//if (!pause_flag)
	//{
	//	// 親クラスの更新処理を呼び出す
	//	__super::Update(delta_second);

	//	//// プレイヤーが死んだら、再スタート
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

	// シーン情報を返却する
	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	// 背景画像の描画
	//DrawRotaGraph(0, 480, 2.0, 0.0, back_ground_image, TRUE);

	// オフセット値を基に画像の描画を行う
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

	// 親クラスの描画処理を呼び出す
	__super::Draw();

	DrawString(50, 50, "ゲーム画面です", GetColor(255, 255, 255), TRUE);

	// UI系の描画処理
	if (pause_flag)
	{
		DrawString(10, 10, " P A U S E ", GetColor(255, 255, 255), TRUE);
	}
}

void InGameScene::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::in_game;
}

/// <summary>
/// 当たり判定確認処理
/// </summary>
/// <param name="target">1つ目のゲームオブジェクト</param>
/// <param name="partner">2つ目のゲームオブジェクト</param>
void InGameScene::HitCheckObject(GameObject* target, GameObject* partner)
{
	// ヌルポチェック
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	// 当たり判定情報を取得
	Collision tc = target->GetCollision();
	Collision pc = partner->GetCollision();

	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{

		// 線分の始点と終点を設定する
		tc.box_location[0] = target->GetLocation();
		pc.box_location[0] = partner->GetLocation();

		// 矩形同士の当たり判定
		if (IsCheckCollision(tc, pc))
		{
			// 当たっていることを通知する
			target->OnHitCollision(partner);
			partner->OnHitCollision(target);
		}

	}

}

/// <summary>
/// ステージマップ（壁）読み込み処理
/// </summary>
void InGameScene::LoadStageMapCSV()
{
	//FILE* fp = NULL;
	//std::string file_name = "Resource/Maps/Book1.csv";

	//// 指定されたファイルを開く
	//errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	//// エラーチェック
	//if (result != 0)
	//{
	//	throw (file_name + "が開けません");
	//}

	//int x = 0;
	//int y = 0;

	//// ファイル内の文字を確認していく
	//while (true)
	//{
	//	// ファイルから1文字抽出する
	//	int c = fgetc(fp);

	//	// 抽出した文字がEOFならループ終了
	//	if (c == EOF)
	//	{
	//		break;
	//	}
	//	// 抽出した文字がGなら、道を生成
	//	else if (c == '1')
	//	{
	//		Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);

	//		CreateObject<BrickBlock>(generate_location);
	//		x++;
	//	}
	//	// 抽出した文字がBなら、壊せるブロックを生成
	//	else if (c == 'B')
	//	{
	//		Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
	//		CreateObject<Block>(generate_location);
	//		x++;
	//	}
	//	// 抽出した文字がハテナなら、ハテナブロックを生成
	//	else if (c == '?')
	//	{
	//		Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
	//		CreateObject<Hatena>(generate_location);
	//		x++;
	//	}
	//	//抽出した文字がDなら、土管を生成
	//	else if (c == 'D')
	//	{
	//		// ファイルから1文字抽出する
	//		int b = fgetc(fp);

	//		//Dの次の文字が1～4の文字だったら対応した画像を設定し生成
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
	//	// 抽出した文字が空白文字なら、生成しないで次の文字を見に行く
	//	else if (c == '0')
	//	{
	//		x++;
	//	}
	//	// 抽出した文字が改行文字なら、次の行を見に行く
	//	else if (c == '\n')
	//	{
	//		x = 0;
	//		y++;
	//	}

	//}

	//// 開いたファイルを閉じる
	//fclose(fp);
}