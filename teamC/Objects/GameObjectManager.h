#pragma once
#include "../Utility/Singleton.h"
#include "GameObject.h"
#include <vector>

class GameObjectManager : public Singleton <GameObjectManager>
{
private:
	std::vector<GameObject*> create_object;
	std::vector<GameObject*> destroy_object;
	std::vector<GameObject*> game_object_list;

public:
	GameObjectManager() :
		create_object(),
		game_object_list(),
		destroy_object()
	{

	}
	virtual ~GameObjectManager()
	{
		// 解放忘れ防止
		Finalize();
	}

public:
/// <summary>
/// 終了時処理
/// </summary>
	virtual void Finalize()
	{
		// オブジェクトリスト内のオブジェクトを破棄する
		DestoryAllObject();

		// 動的配列の解放
		if (!create_object.empty())
		{
			create_object.clear();
		}
		if (!destroy_object.empty())
		{
			destroy_object.clear();
		}
	}

	//CreateしたObjectをgame_object_listの入れる処理
	void CheckCreateObject()
	{
		if (!create_object.empty())
		{
			for (GameObject* obj : create_object)
			{
				//オブジェクトのZレイヤー情報を入れる
				int z_layer = obj->GetZLayer();
				std::vector<GameObject*>::iterator itr = game_object_list.begin();

				//オブジェクトのZレイヤーの値を比較し、挿入する場所を決める。
				for (; itr != game_object_list.end(); itr++)
				{
					if (z_layer < (*itr)->GetZLayer())
					{
						break;
					}
				}
				//もしエネミーだったらenemy_listに挿入する。それ以外はgame_objectに入れる
				/*if (obj->GetCollision().object_type == eEnemy)
				{
					game_enemy_list.push_back(obj);
				}
				else
				{
					game_object_list.insert(itr, obj);
				}*/

				game_object_list.insert(itr, obj);
			}
			//オブジェクト生成リストを解放する
			create_object.clear();

		}
	}

	void CheckDstroyObject()
	{
		// 破棄リスト内が空でない場合、リスト内のオブジェクトを破棄する
		if (!destroy_object.empty())
		{
			for (GameObject* obj : destroy_object)
			{
				std::vector<GameObject*>::iterator itr = game_object_list.begin();	// オブジェクトリストの先頭
				// リストの末尾になるまで走査する
				for (; itr != game_object_list.end(); itr++)
				{
					// リスト内にあれば、削除する
					if ((*itr) == obj)
					{
						game_object_list.erase(itr);
						obj->Finalize();
						delete obj;
						break;
					}
				}
			}
			// 動的配列の開放
			destroy_object.clear();

			// リストが空なら処理を終了する
			if (destroy_object.empty())
			{
				return;
			}
			// リスト内のオブジェクトを削除する
			for (GameObject* obj : destroy_object)
			{
				obj->Finalize();
				delete obj;
			}
			// リストの解放
			destroy_object.clear();
		}
	}
	const std::vector<GameObject*>& GetObjectsList() const
	{
		return game_object_list;
	}

	template <class OBJECT>
	OBJECT* CreateGameObject(const Vector2D& generate_location)
	{
		OBJECT* new_instance = new OBJECT();

		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		if (new_object == nullptr)
		{
			delete new_instance;

			throw ("ゲームオブジェクトが生成できませんでした\n");
			return nullptr;
		}

		new_object->Initialize();

		new_object->SetLocation(generate_location);

		create_object.push_back(new_object);

		CheckCreateObject();

		return new_instance;
	}

	void DestroyGameObject(GameObject* target)
	{
		if (target == nullptr)
		{
			return;
		}

		for (GameObject* obj : destroy_object)
		{
			if (obj == target)
			{
				return;
			}
		}

		destroy_object.push_back(target);
	}

	void HitCheck()
	{
		for (int i = 0; i < game_object_list.size(); i++)
		{
			if (game_object_list[i]->GetMobility() == false)
			{
				continue;
			}

			for (int j = 0; j < game_object_list.size(); j++)
			{
				if (i == j)
				{
					continue;
				}

				CheckCollision(game_object_list[i], game_object_list[j]);
			}
		}
	}

	void CheckCollision(GameObject* target, GameObject* partner)
	{
		bool flag = false;

		if (target == nullptr || partner == nullptr)
		{
			return;
		}

		Collision tc = target->GetCollision();
		Collision pc = partner->GetCollision();


		if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
		{

			tc.pivot = target->GetLocation();
			pc.pivot = partner->GetLocation();

			if (tc.IsCheckHitCollision(tc, pc))
			{
				target->OnHitCollision(partner);
				partner->OnHitCollision(target);
			}

		}
	}

private:
		/// <summary>
		/// シーン内オブジェクト破棄処理
		/// </summary>
		void DestoryAllObject()
		{
			// オブジェクトリストが空なら処理を終了する
			if (game_object_list.empty())
			{
				return;
			}
			// オブジェクトリスト内のオブジェクトを削除する
			for (GameObject* obj : game_object_list)
			{
				obj->Finalize();
				delete obj;
			}
			// 動的配列の解放
			game_object_list.clear();
		}

};
