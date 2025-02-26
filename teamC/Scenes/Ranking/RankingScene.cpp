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
	__super::Initialize();

	// 背景画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;


	back_ground_image = rm->GetImageResource("Resource/Images/Title.jpeg")[0];

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

	DrawGraph(0, 0, back_ground_image, TRUE);
	
	SetFontSize(50);

	DrawFormatString(180, 20, GetColor(255, 255, 255), "ランキング");

	// ランキングの描画
	for (size_t i = 0; i < ranking.size(); ++i) {
		DrawFormatString(180, 100 + i * 70, GetColor(255, 255, 255), "%d位: %d点", i + 1, ranking[i]);
	}

	
}

void RankingScene::AddScore(int score) {
	LoadRanking();
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
	std::ofstream file("Resource/ranking.dat", std::ios::out);
	if (file.is_open()) {
		for (int score : ranking) {
			file << score << "\n";
		}
		file.close();
	}
}

void RankingScene::LoadRanking() {
	std::ifstream file("Resource/ranking.dat", std::ios::in);
	ranking.clear(); // 一旦クリア
	int score;
	while (file >> score) {
		ranking.push_back(score);
	}
	file.close();
	std::sort(ranking.rbegin(), ranking.rend()); // 降順ソート
}