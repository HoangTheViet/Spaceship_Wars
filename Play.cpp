#include "Play.h"

using namespace std;


void Play::createMatrix(int size) {
	vector<int> move = { 1, 1, -1, -1 };
	for (int i = 0; i < 2; i++) {
		int pos;
		bool choosen = false;
		while (choosen == false) {

			// random a cell;
			pos = random(0, 99);
			int lead = pos / 10;
			int trail = pos % 10;
			while (a1[lead][trail] != 0) {
				pos = random(0, 99);
				lead = pos / 10;
				trail = pos % 10;
			}

			// check move;
			int m;
			bool kt = false;
			while (kt == false) {
				m = random(0, 3);
				s.insert(m);
				int run = move[m];
				if (checkAI(lead, trail, run, size)) {
					kt = true;
				}
				else {
					if (s.size() == 4) break;
					continue;
				}
			}

			// after check;
			if (kt == false) {
				s.clear();
				a1[lead][trail] = size;
				continue;
			}
			else {
				mark(lead, trail, move[m], size);
				choosen = true;
			}
		}

		// fix cell
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (a1[i][j] != 1 && a1[i][j] != 0) a1[i][j] = 0;
			}
		}
		s.clear();
	}
}

bool Play::checkAI(int i, int j, int m, int size) {
	int fact = 1;
	if (m == 0 || m == 2) {
		for (int k = 0; k < size; k++) {
			int res = j + fact * m;
			if (a1[i][res] != 0 || res < 0 || res >= 10) return false;
			fact++;
		}
	}
	else {
		for (int k = 0; k < size; k++) {
			int res = i + fact * m;
			if (a1[res][j] != 0 || res < 0 || res >= 10) return false;
			fact++;
		}
	}
	return true;
}

void Play::mark(int i, int j, int m, int size) {
	vector<int> runner;
	int fact = 1;
	if (m == 0 || m == 2) {
		for (int k = 0; k < size; k++) {
			a1[i][j + fact * m] = 1;
			runner.push_back(i * 10 + j + fact * m);
			fact++;
		}
	}
	else {
		for (int k = 0; k < size; k++) {
			a1[i + fact * m][j] = 1;
			runner.push_back((i + fact * m) * 10 + j);
			fact++;
		}
	}
	saveAI.push_back(runner);
}

void Play::matrixForAI(int size) {
	for (int l = 0; l < 3; l++) {
		createMatrix(size);
		size--;
	}
}

int Play::random(int minn, int maxx) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(minn, maxx);
	return dist(gen);
}

void Play::free() {
    if (h4.drawed() == false) h4.free();
    if (v4.drawed() == false) v4.free();
    if (h3.drawed() == false) h3.free();
    if (v3.drawed() == false) v3.free();
    if (h2.drawed() == false) h2.free();
    if (v2.drawed() == false) v2.free();
    step.free();
    notice.free();
    green.free();
}

void Play::load(SDL_Renderer* &ren, TTF_Font* &font) {
    for (int i = 0; i < 100; i++) {
        toShoot.push_back(i);
    }

	h4.loadFromFile(ren, "image/h4.png");
	h4.checkLoad();

	v4.loadFromFile(ren, "image/v4.png");
	v4.checkLoad();

	h3.loadFromFile(ren, "image/h3.png");
	h3.checkLoad();
  
	v3.loadFromFile(ren, "image/v3.png");
	v3.checkLoad();

	h2.loadFromFile(ren, "image/h2.png");
	h2.checkLoad();

	v2.loadFromFile(ren, "image/v2.png");
	v2.checkLoad();

	notice.loadFromFile(ren, "image/notice.png");
	notice.checkLoad();

	green.loadFromFile(ren, "image/Green.png");
	green.checkLoad();
    // in game

    yours.loadTTF(ren, font, 250, 0, 0, "YOURS:");
    enemy.loadTTF(ren, font, 250, 0, 0, "ENEMY:");

    yours.checkLoad();
    enemy.checkLoad();


    //starting the game
    TTF_Font* newfont = TTF_OpenFont("TtfAndMixer/Vdj.ttf", 80);
    one.loadTTF(ren, newfont, 250, 250, 0, to_string(1));
    two.loadTTF(ren, newfont, 250, 250, 0, to_string(2));
    three.loadTTF(ren, newfont, 250, 250, 0, to_string(3));
    START.loadTTF(ren, newfont, 250, 250, 0, "START!");
    Pturn.loadTTF(ren, font, 250, 250, 0, "YOUR TURN");
    Aturn.loadTTF(ren, font, 250, 250, 0, "BOT'S TURN");
    TTF_CloseFont(newfont);

    // playing
    rocket.loadFromFile(ren, "image/KimJongUn3.png");
    rocket.checkLoad();

    boom.loadFromFile(ren, "image/Explo.png");
    boom.checkLoad();

    miss.loadFromFile(ren, "image/missEffect.png");
    miss.checkLoad();

    xred.loadFromFile(ren, "image/XRed.png");
    xred.checkLoad();

    red.loadFromFile(ren, "image/Red.png");
    red.checkLoad();

    hit = Mix_LoadWAV("TtfAndMixer/newSound.wav");
    if (hit == nullptr) logSDLError(std::cout, "the sound effect of hit was not uploaded ", true);
    
    fly = Mix_LoadWAV("TtfAndMixer/launcher_out.wav");
    if(fly == nullptr) logSDLError(std::cout, "the sound effect of fly was not uploaded ", true);

    small = Mix_LoadWAV("TtfAndMixer/smallSound.wav");
    if(small == nullptr) logSDLError(std::cout, "the sound effect of small sound was not uploaded ", true);
}

void Play::matrixForPlayer(int size, string s, SDL_Renderer* &ren, StartScreen& scr, vipText& background, bool& running) {

	step.free();
	step.loadFromFile(ren, s.c_str());
	step.checkLoad();
	step.render(ren, 0, 0, 295, 460, step.getWidth(), step.getHeight());

    SDL_Event k;
    bool run = true;
    int dx = 0; int dy = 0;
    vector<int> runner;
    bool check = true;

    while (run) {
        //event
        while (SDL_PollEvent(&k) != 0) {
            if (k.type == SDL_QUIT) run = false;
            if (k.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&dx, &dy);
            }
        }
        // get the position
        if ((dx >= 40 && dx <= 440) && (dy >= 40 && dy <= 440) && check == true) {
            if (!pick(ren, runner, green, dx, dy)) continue;
        }
        else if ((dy >= 540 && dy <= 590) && check == true) {
            if (dx >= 370 && dx <= 450) {// if press reset
                scr.MatrixScreen(background, ren);
                step.render(ren, 0, 0, 295, 460, step.getWidth(), step.getHeight());
                renderEx(ren);
            }// if press OK
            else if (dx > 450 && dx <= 530) {
                string str = checkUsers(runner, size);
                if (str == "wrong") {
                    runner.clear();
                    check = false;
                    scr.MatrixScreen(background, ren);
                    renderEx(ren);
                    notice.render(ren, 0, 0, 295, 460, notice.getWidth(), notice.getHeight());
                }
                else if (str == "h4") {
                    maker(h4, runner, scr, ren, background);
                    return;
                }
                else if (str == "v4") {
                    maker(v4, runner, scr, ren, background);
                    return;
                }
                else if (str == "h3") {
                    maker(h3, runner, scr, ren, background);
                    return;
                }
                else if (str == "v3") {
                    maker(v3, runner, scr, ren, background);
                    return;
                }
                else if (str == "h2") {
                    maker(h2, runner, scr, ren, background);
                    return;
                }
                else if (str == "v2") {
                    maker(v2, runner, scr, ren, background);
                    return;
                }
            }
        }//quit or continue
        else if (dy >= 580 && dy <= 620 && check == false) {
            if (dx >= 450 && dx <= 530) {
                running = false;
                break;
            }
            else if (dx >= 370 && dx <= 450) {
                check = true;
                scr.MatrixScreen(background, ren);
                step.render(ren, 0, 0, 295, 460, step.getWidth(), step.getHeight());
                renderEx(ren);
            }
        }
        SDL_RenderPresent(ren);

    }
}

string Play::checkUsers(vector<int>& v, int size) {
    if (v.size() != size) return "wrong";

    sort(v.begin(), v.end());
    int countV = 0;
    int countH = 0;

    for (int i = 0; i < v.size() - 1; i++) {
        if (v[i + 1] - v[i] == 10) countV++;
    }
    for (int i = 0; i < v.size() - 1; i++) {
        if (v[i + 1] - v[i] == 1) countH++;
    }
    if (size == 4) {
        if (countV == v.size() - 1) {
            return "v4";
        }
        else if (countH == v.size() - 1) {
            return "h4";
        }
    }
    else if (size == 3) {
        if (countV == v.size() - 1) {
            return "v3";
        }
        else if (countH == v.size() - 1) {
            return "h3";
        }
    }
    else if (size == 2) {
        if (countV == v.size() - 1) {
            return "v2";
        }
        else if (countH == v.size() - 1) {
            return "h2";
        }
    }
    return "wrong";
}

void Play::renderEx(SDL_Renderer* &ren) {
    for (int i = 0; i < toRender.size(); i++) {
        toRender[i].render(ren, 0, 0, posToRen[i][0], posToRen[i][1], toRender[i].getWidth(), toRender[i].getHeight());
    }
}

void Play::maker(vipText& h, vector<int>& runner, StartScreen& scr, SDL_Renderer* &ren, vipText& background) {
    vector<int> r;
    for (int i = 0; i < runner.size(); i++) {
        a2[runner[i] / 10][runner[i] % 10] = 1;
    }
    int x = runner[0] % 10 + 1;
    int y = runner[0] / 10 + 1;
    scr.MatrixScreen(background, ren);
    renderEx(ren);
    h.render(ren, 0, 0, x * 40, y * 40, h.getWidth(), h.getHeight());
    toRender.push_back(h);
    h.fixed();
    r.push_back(x * 40);
    r.push_back(y * 40);
    posToRen.push_back(r);
    savePlayer.push_back(runner);
}

bool Play::pick(SDL_Renderer* &ren, vector<int>& runner, vipText& green, int x, int y) {
    int row = y / 40 - 1;
    int coll = x / 40 - 1;
    for (int i = 0; i < runner.size(); i++) {
        if (runner[i] == row * 10 + coll) return false;
    }
    if (a2[row][coll] != 0) return false;
    runner.push_back(row * 10 + coll);
    green.render(ren, 0, 0, (coll + 1) * 40, (row + 1) * 40, green.getWidth(), green.getHeight());
    SDL_RenderPresent(ren);
    return true;
}

// last step

void Play::renderScore( SDL_Renderer* &ren, TTF_Font* &font, int& Y, int& E) {
    scoreY.free();
    scoreE.free();

    scoreY.loadTTF(ren, font, 0, 255, 255, to_string(Y));
    scoreE.loadTTF(ren, font, 0, 255, 255, to_string(E));

    yours.render(ren, 0, 0, 160, 460, yours.getWidth(), yours.getHeight());
    enemy.render(ren, 0, 0, 580, 460, enemy.getWidth(), enemy.getHeight());
    scoreY.render(ren, 0, 0, 160 + yours.getWidth(), 460, scoreY.getWidth(), scoreY.getHeight());
    scoreE.render(ren, 0, 0, 580 + enemy.getWidth(), 460, scoreE.getWidth(), scoreE.getHeight());
  
}

void Play::begin(SDL_Renderer*& ren, StartScreen& scr, vipText& background) {

    three.render(ren, 0, 0, 420, 500, three.getWidth(), three.getHeight());
    SDL_RenderPresent(ren);
    SDL_Delay(1000);
    scr.MatrixScreen(background, ren);
    renderEx(ren);

    two.render(ren, 0, 0, 420, 500, two.getWidth(), two.getHeight());
    SDL_RenderPresent(ren);
    SDL_Delay(1000);
    scr.MatrixScreen(background, ren);
    renderEx(ren);

    one.render(ren, 0, 0, 420, 500, one.getWidth(), one.getHeight());
    SDL_RenderPresent(ren);
    SDL_Delay(1000);
    scr.MatrixScreen(background, ren);
    renderEx(ren);

    START.render(ren, 0, 0, 300, 500, START.getWidth(), START.getHeight());
    SDL_RenderPresent(ren);
    SDL_Delay(1000);
    scr.MatrixScreen(background, ren);
    renderEx(ren);

    one.free();
    two.free();
    three.free();
    START.free();
}


void Play::flyingRocket(SDL_Renderer* &ren, TTF_Font* &font, StartScreen& scr, vipText& background, int x, int y, int &Y, int &E, int &type) {
    x -= rocket.getWidth() / 2;
    int posY = 700;
    int count = 8;
    int increase = rocket.getHeight() / 10;
    int w = rocket.getWidth();
    int start = rocket.getHeight() - increase;

    Mix_PlayChannel(2, fly, 0);
    while (posY > y) {
        while (count--) {
            scr.MatrixScreen(background, ren);
            renderEx(ren);
            renderTurn(ren, font, scr, background, Y, E, type);
            rocket.render(ren, 0, start, x, posY, w, increase);
            SDL_RenderPresent(ren);
            posY -= 10;
            SDL_Delay(30);
        }
        count = 8;
        start -= increase;
        if (start < 0) start = rocket.getHeight() - increase;
        SDL_Delay(20);
    }
}

void Play::Miss(SDL_Renderer*& ren, TTF_Font*& font, StartScreen& scr, vipText& background, int x, int y, int& Y, int& E, int& type) {
    int increase = miss.getHeight() / 8;
    int start = miss.getHeight() - increase;
    x -= miss.getWidth() / 2;
    y -= increase;
    Mix_PlayChannel(2, small, 0);
    while (true) {
        scr.MatrixScreen(background, ren);
        renderEx(ren);
        renderTurn(ren, font, scr, background, Y, E, type);
        miss.render(ren, 0, start, x, y, miss.getWidth(), increase);
        SDL_RenderPresent(ren);
        start -= increase;
        if (start < 0) {
            scr.MatrixScreen(background, ren);
            renderEx(ren);
            renderTurn(ren, font, scr, background, Y, E, type);
            SDL_RenderPresent(ren);
            break;
        }
        SDL_Delay(60);
    }
}



void Play::Boom(SDL_Renderer*& ren, TTF_Font*& font, StartScreen& scr, vipText& background, int x, int y, int& Y, int& E, int& type) {
    int increase = boom.getHeight() / 24;
    int start = boom.getHeight() - increase;
    x -= boom.getWidth() / 2;
    y -= increase;

    Mix_PlayChannel(2, hit, 0);
    while (true) {
        scr.MatrixScreen(background, ren);
        renderEx(ren);
        renderTurn(ren, font, scr, background, Y, E, type);
        boom.render(ren, 0, start, x, y, boom.getWidth(), increase);
        SDL_RenderPresent(ren);
        start -= increase;
        if (start < 0) {
            scr.MatrixScreen(background, ren);
            renderEx(ren);
            renderTurn(ren, font, scr, background, Y, E, type);
            SDL_RenderPresent(ren);
            break;
        }
        SDL_Delay(60);
    }
}

void Play:: MissOrHit(SDL_Renderer* ren, StartScreen& scr, vipText& background, TTF_Font*& font, int x, int y, int& Y, int& E, int& type, bool& previous, bool& first, int& current) {
    
    if (type % 2 == 0) {
        int res = ((x / 40) - 12) * 10 + (y / 40);
        bool hit = false;
        for (int i = 0; i < saveAI.size(); i++) {
            for (int j = 0; j < saveAI[i].size(); j++) {
                if (saveAI[i][j] == res) {
                    saveAI[i].erase(saveAI[i].begin() + j);
                    hit = true;
                    Boom(ren, font, scr, background, x, y, Y, E, type);
                    scr.MatrixScreen(background, ren);
                    renderEx(ren);
                    renderTurn(ren, font, scr, background, Y, E, type);
                    xred.render(ren, 0, 0, x - 20, y - 20, xred.getWidth(), xred.getHeight());
                    toRender.push_back(xred);
                    vector<int> pos;
                    pos.push_back(x - 20);
                    pos.push_back(y - 20);
                    posToRen.push_back(pos);
                    SDL_RenderPresent;
                    break;
                }
            }
        }
        if (hit == false) {
            Miss(ren, font, scr, background, x, y, Y, E, type);
            red.render(ren, 0, 0, x - 20, y - 20, red.getWidth(), red.getHeight());
            toRender.push_back(red);
            vector<int> pos;
            pos.push_back(x - 20);
            pos.push_back(y - 20);
            posToRen.push_back(pos);
        }
        for (int i = 0; i < saveAI.size(); i++) {
            if (saveAI[i].size() == 0) {
                saveAI.erase(saveAI.begin() + i);
                E--;
                scr.MatrixScreen(background, ren);
                renderEx(ren);
                renderTurn(ren, font, scr, background, Y, E, type);
                break;
            }
        }
    }
    else {
        int res = ((y - 20) / 40 - 1) * 10 + ((x - 20) / 40 - 1);
        bool hit = false;
        for (int i = 0; i < savePlayer.size(); i++) {
            for (int j = 0; j < savePlayer[i].size(); j++) {
                if (savePlayer[i][j] == res) {
                    previous = true;
                    first = true;
                    hitman.push({ x, y });
                    savePlayer[i].erase(savePlayer[i].begin() + j);
                    hit = true;
                    Boom(ren, font, scr, background, x, y, Y, E, type);
                    scr.MatrixScreen(background, ren);
                    renderEx(ren);
                    renderTurn(ren, font, scr, background, Y, E, type);
                    xred.render(ren, 0, 0, x - 20, y - 20, xred.getWidth(), xred.getHeight());
                    toRender.push_back(xred);
                    vector<int> pos;
                    pos.push_back(x - 20);
                    pos.push_back(y - 20);
                    posToRen.push_back(pos);
                    SDL_RenderPresent;
                    break;
                }
            }
        }
        if (hit == false) {
            first = false;
            Miss(ren, font, scr, background, x, y, Y, E, type);
            red.render(ren, 0, 0, x - 20, y - 20, red.getWidth(), red.getHeight());
            toRender.push_back(red);
            vector<int> pos;
            pos.push_back(x - 20);
            pos.push_back(y - 20);
            posToRen.push_back(pos);
        }
        for (int i = 0; i < savePlayer.size(); i++) {
            if (savePlayer[i].size() == 0) {
                savePlayer.erase(savePlayer.begin() + i);
                Y--;
                scr.MatrixScreen(background, ren);
                renderEx(ren);
                renderTurn(ren, font, scr, background, Y, E, type);
                break;
            }
        }
        if (current > Y) {
            current = Y;
            previous = false;
            first = false;
            while (!hitman.empty()) hitman.pop();
            move = { 0, 1, 2, 3 };
        }
    }
}

void Play::renderTurn(SDL_Renderer*& ren, TTF_Font*& font, StartScreen& scr, vipText& background, int& Y, int& E, int &type) {
    if (type % 2 == 0) {
        scr.MatrixScreen(background, ren);
        renderEx(ren);
        renderScore(ren, font, Y, E);
        Pturn.render(ren, 0, 0, 350, 500, Pturn.getWidth(), Pturn.getHeight());
        SDL_RenderPresent(ren);
    }
    else {
        scr.MatrixScreen(background, ren);
        renderEx(ren);
        renderScore(ren, font, Y, E);
        Aturn.render(ren, 0, 0, 350, 500, Aturn.getWidth(), Aturn.getHeight());
        SDL_RenderPresent(ren);
    }
}

vector<int> Play::shoot(bool& previous, bool& first) {
    if (previous == false) {
        int k = random(0, toShoot.size() - 1);
        int resu = toShoot[k];
        toShoot.erase(toShoot.begin() + k);
        int x = ((resu % 10) + 1) * 40 + 20;
        int y = ((resu / 10) + 1) * 40 + 20;
        a2[resu / 10][resu % 10] = 2;
        return { x, y };
    }
    else {// res[0] = x, res[1] = y; x= coll, y = row
        if (first == false) {
            
            while (hitman.size() != 1) hitman.pop();
            vector<int> res = hitman.top();
            int p = random(0, move.size() - 1);
            while (true) {
                int row = (res[1] + r[p] * 40) / 40 - 1;
                int coll = (res[0] + c[p] * 40) / 40 - 1;
                if (legal(res[0] + c[p] * 40, res[1] + r[p] * 40) && a2[row][coll] == 0) break;
                p = random(0, move.size() - 1);
            }
            movement = move[p];
            move.erase(move.begin() + p);
            int lookFor = ((res[1] + r[movement] * 40) / 40 - 1) * 10 + ((res[0] + c[movement] * 40) / 40 - 1);
            for (int i = 0; i < toShoot.size(); i++) {
                if (toShoot[i] == lookFor) {
                    toShoot.erase(toShoot.begin() + i);
                    break;
                }
            }
            a2[lookFor / 10][lookFor % 10] = 2;
            return { res[0] + c[p] * 40, res[1] + r[p] * 40 };
        }
        else {
            vector<int> res = hitman.top();
            int lookFor = ((res[1] + r[movement] * 40) / 40 - 1) * 10 + ((res[0] + c[movement] * 40) / 40 - 1);
            if (!legal(res[0] + c[movement] * 40, res[1] + r[movement] * 40) || a2[lookFor / 10][lookFor % 10] != 0) {
                first = false;
                while (hitman.size() != 1) hitman.pop();
                return shoot(previous, first);
            }
            for (int i = 0; i < toShoot.size(); i++) {
                if (toShoot[i] == lookFor) {
                    toShoot.erase(toShoot.begin() + i);
                    break;
                }
            }
            a2[lookFor / 10][lookFor % 10] = 2;
            return { res[0] + c[movement] * 40, res[1] + r[movement] * 40 };
        }
    }
}



bool Play::legal(int x, int y) {
    return (x > 40 && x < 440 && y > 40 && y < 440);
}




	