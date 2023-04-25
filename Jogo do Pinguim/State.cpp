#include "State.h"
#include "Face.h"
#include "Vec2.h"

State::State() {
	quitRequested = false;

	bg = *new Sprite("img/ocean.jpg");
	music.Open("audio/stageState.ogg");
	music.Play();
}

State::~State() {
	while (objectArray.empty() == false) {
		objectArray.erase(objectArray.end() - 1);
	}
	objectArray.clear();
}

void State::LoadAssets() {
	// carregar imagens e musicas aqui quando possivel
}

void State::Update(float dt) {
	Input();
	int i = 0;
	GameObject* go;
	while (objectArray.begin() + i != objectArray.end()) {
		go = objectArray[i];
		go->Update(dt);
		i++;
	}

	i = 0;
	while (objectArray.begin() + i != objectArray.end()) {
		go = objectArray[i];
		if (go->IsDead()) {
			DeleteObject(*go);
		}
		i++;
	}
}

void State::Render() {
	int i = 0;
	GameObject* go;
	while (objectArray.begin() + i != objectArray.end()) {
		go = objectArray[i];
		go->Render();
		i++;
	}
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::AddObject(int mouseX, int mouseY) {
	GameObject newGO;

	// mudar para fazer x e y serem o centro do novo sprite
	newGO.box.x = mouseX;
	newGO.box.y = mouseY;

	Sprite* enemy = new Sprite("img/penguinface.png");
	newGO.AddComponent(enemy);

	Sound* boom = new Sound(newGO, "audio/boom.wav");
	newGO.AddComponent(*boom);

	Face* penguinFace = new Face(newGO);
	newGO.AddComponent(*penguinFace);

}

void State::DeleteObject(GameObject& go) {

}

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}

		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				Vec2& coordinates = new Vec2(mouseX, mouseY);
				if(go->box.IsInside(coordinates)) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}
