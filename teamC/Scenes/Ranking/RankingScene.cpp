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
	// ���͏����擾
	InputManager* input = InputManager::GetInstance();

	// �^�C�g���V�[���ɑJ�ڂ���
	if (input->GetKeyState(KEY_INPUT_SPACE) == Pressed)
	{
		return eSceneType::eTitle;
	}
	if (input->GetButtonState(XINPUT_BUTTON_START) == Pressed ||
		input->GetButtonState(XINPUT_BUTTON_A) == eInputState::Pressed)
	{
		return eSceneType::eTitle;
	}

	// �e�N���X�̍X�V�������Ăяo��
	return GetNowSceneType();
}

void RankingScene::Draw() const
{
	// �e�N���X�̕`�揈�����Ăяo��
	//__super::Draw();

	SetFontSize(50);

	DrawFormatString(150, 20, GetColor(255, 255, 255), "�����L���O");

	// �����L���O�̕`��
	for (size_t i = 0; i < ranking.size(); ++i) {
		DrawFormatString(100, 100 + i * 50, GetColor(255, 255, 255), "%d��: %d�_", i + 1, ranking[i]);
	}

	// UI�̕`��
	DrawFormatString(10, 640, GetColor(255, 0, 0), "Space key pressed back title");
	//SetFontSize(16);
}

void RankingScene::AddScore(int score) {
	ranking.push_back(score);
	std::sort(ranking.rbegin(), ranking.rend()); // �~���\�[�g
	if (ranking.size() > MAX_RANKING) {
		ranking.pop_back(); // 5�ʂ�艺�̃X�R�A���폜
	}
	SaveRanking();
}

void RankingScene::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
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
	ranking.clear(); // ��U�N���A
	int score;
	while (file >> score) {
		ranking.push_back(score);
	}
	file.close();
	std::sort(ranking.rbegin(), ranking.rend()); // �~���\�[�g
}