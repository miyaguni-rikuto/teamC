#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <string>
#include <vector>

class ResourceManager : public Singleton<ResourceManager>
{
private:
	std::unordered_map<std::string, std::vector<int>> image_container;		//�摜�R���e�i
	std::unordered_map<std::string, int> sound_container;					//�����R���e�i

public:
	const std::vector<int>& GetImageResource(const std::string& file_name, int all_num = 1, int num_x = 1, int num_y = 1, int size_x = 0, int size_y = 0);
	const int& GetSoundResource(const std::string& file_path);
	void UnloadAllResourceData();

private:
	void CreateImageResource(const std::string& file_path);			//�ǂݍ��񂾉摜���R���e�i�ɓ����
	void CreateImagesResource(std::string file_name, int all_num, int num_x, int num_y, int size_x, int size_y);		//�摜�̓ǂݍ���
	void CreateSoundsResource(std::string file_path);				//�����̓ǂݍ���
	void UnloadImageResourceData();			//�������̊J��
	void UnloadSoundResourceData();			//�������̊J��
};

