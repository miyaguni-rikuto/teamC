#include "RankingScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

RankingScene::RankingScene()
{

}

RankingScene::~RankingScene()
{

}

RankingScene& RankingScene::GetInstance() {
	static RankingScene instance;
	return instance;
}

void RankingScene::Initialize()
{
	LoadRanking();
}

eSceneType RankingScene::Update(float delta_second)
{
	// 入力情報を取得
	InputManager* input = InputManager::GetInstance();

	// タイトルシーンに遷移する
	if (input->GetKeyState(KEY_INPUT_SPACE) == Pressed)
	{
		return eSceneType::eTitle;
	}
	if (input->GetButtonState(XINPUT_BUTTON_START) == Pressed ||
		input->GetButtonState(XINPUT_BUTTON_A) == eInputState::Pressed)
	{
		return eSceneType::eTitle;
	}

	// 親クラスの更新処理を呼び出す
	return GetNowSceneType();
}

void RankingScene::Draw() const
{
	// 親クラスの描画処理を呼び出す
	//__super::Draw();

	SetFontSize(50);

	DrawFormatString(150, 20, GetColor(255, 255, 255), "ランキング");

	// ランキングの描画
	for (size_t i = 0; i < ranking.size(); ++i) {
		DrawFormatString(100, 100 + i * 50, GetColor(255, 255, 255), "%d位: %d点", i + 1, ranking[i]);
	}

	// UIの描画
	DrawFormatString(10, 640, GetColor(255, 0, 0), "Space key pressed back title");
	//SetFontSize(16);
}

void RankingScene::AddScore(int score) {
	ranking.push_back(score);
	std::sort(ranking.rbegin(), ranking.rend()); // 降順ソート
	if (ranking.size() > MAX_RANKING) {
		ranking.pop_back(); // 5位より下のスコアを削除
	}
	SaveRanking();
}

void RankingScene::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

eSceneType RankingScene::GetNowSceneType() const
{
	return eSceneType::eRanking;
}

void RankingScene::SaveRanking() {
	std::ofstream file("ranking.dat", std::ios::out);
	if (file.is_open()) {
		for (int score : ranking) {
			file << score << "\n";
		}
		file.close();
	}
}

void RankingScene::LoadRanking() {
	std::ifstream file("ranking.dat", std::ios::in);
	ranking.clear(); // 一旦クリア
	int score;
	while (file >> score) {
		ranking.push_back(score);
	}
	file.close();
	std::sort(ranking.rbegin(), ranking.rend()); // 降順ソート
}