#include "State.h"
#include "Face.h"
#include "Vec2.h"

State::State() {
	quitRequested = false;

	// Cria GO ambient e atribui ele a Sprite do BG
	GameObject* ambient = new GameObject;
	Component* bg = new Sprite(*ambient, "img/ocean.jpg");
	ambient->AddComponent(bg);

	// adiciona ambient a lista de GOs
	AddObject(ambient);

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
		go = (GameObject*)objectArray[i].get();
		go->Update(dt);
		i++;
	}

	i = 0;
	while (objectArray.begin() + i != objectArray.end()) {
		go = (GameObject*)objectArray[i].get();
		if (go->IsDead()) {
			DeleteObject(go);
		}
		i++;
	}
}

void State::Render() {
	int i = 0;
	GameObject* go;
	while (objectArray.begin() + i != objectArray.end()) {
		go = (GameObject*)objectArray[i].get();
		go->Render();
		i++;
	}
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::AddObjectClick(int mouseX, int mouseY) {
	GameObject* newGO = new GameObject;

	// mudar para fazer x e y serem o centro do novo sprite
	newGO->box.x = mouseX;
	newGO->box.y = mouseY;

	Sprite* enemy = new Sprite(*newGO, "img/penguinface.png");
	newGO->AddComponent(enemy);

	Sound* boom = new Sound(*newGO, "audio/boom.wav");
	newGO->AddComponent(boom);

	Face* penguinFace = new Face(*newGO);
	newGO->AddComponent(penguinFace);

	objectArray.emplace_back(newGO);
}

void State::AddObject(GameObject* go) {
	objectArray.emplace_back(go);
}

void State::DeleteObject(GameObject* go) {
	int size = objectArray.size(), i = 0;
	while (i < size) {
		if (go == (GameObject*)objectArray[i].get()) {
			objectArray.erase(objectArray.begin() + i);
			return;
		}
		i++;
	}
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
				cout << "FOR" << endl;
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				Vec2 coordinates = *new Vec2((float)mouseX, (float)mouseY);
				if(go->box.IsInside(coordinates)) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						cout << "DAMAGE" << endl;
						face->Damage(rand() % 10 + 10);
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
				Vec2 objPos = Vec2( 200, 0 ).Rotate( -M_PI + M_PI*(rand() % 1001)/500.0 ) + Vec2((float)mouseX, (float)mouseY );
				AddObjectClick((int)objPos.x, (int)objPos.y);
			}
		}
	}
}
