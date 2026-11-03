# include <Siv3D.hpp> // Siv3D v0.6.16

void Main()
{
	while (System::Update()){
		if (Scene::Time() > 5.0f){
			System::Exit();
		}
	}
}
