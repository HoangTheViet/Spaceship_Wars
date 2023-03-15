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
			while (a[lead][trail] != 0) {
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
				a[lead][trail] = size;
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
				if (a[i][j] != 1 && a[i][j] != 0) a[i][j] = 0;
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
			if (a[i][res] != 0 || res < 0 || res >= 10) return false;
			fact++;
		}
	}
	else {
		for (int k = 0; k < size; k++) {
			int res = i + fact * m;
			if (a[res][j] != 0 || res < 0 || res >= 10) return false;
			fact++;
		}
	}
	return true;
}

void Play::mark(int i, int j, int m, int size) {
	vector<int> runner;
	runner.push_back(i * 10 + j);
	int fact = 1;
	if (m == 0 || m == 2) {
		for (int k = 0; k < size; k++) {
			a[i][j + fact * m] = 1;
			runner.push_back(i * 10 + j + fact * m);
			fact++;
		}
	}
	else {
		for (int k = 0; k < size; k++) {
			a[i + fact * m][j] = 1;
			runner.push_back((i + fact * m) * 10 + j);
			fact++;
		}
	}
	save.push_back(runner);
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
    h4.free();
    v4.free();
    h3.free();
    v3.free();
    h2.free();
    v2.free();
    step.free();
    notice.free();
    green.free();
}

void Play::load(SDL_Renderer* ren) {
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
}

void Play::matrixForPlayer(int size, string s, SDL_Renderer* ren, StartScreen& scr, vipText& background, bool& running) {

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

void Play::renderEx(SDL_Renderer* ren) {
    for (int i = 0; i < toRender.size(); i++) {
        toRender[i].render(ren, 0, 0, posToRen[i][0], posToRen[i][1], toRender[i].getWidth(), toRender[i].getHeight());
    }
}

void Play::maker(vipText& h, vector<int>& runner, StartScreen& scr, SDL_Renderer* ren, vipText& background) {
    vector<int> r;
    for (int i = 0; i < runner.size(); i++) {
        a[runner[i] / 10][runner[i] % 10] = 1;
    }
    int x = runner[0] % 10 + 1;
    int y = runner[0] / 10 + 1;
    scr.MatrixScreen(background, ren);
    renderEx(ren);
    h.render(ren, 0, 0, x * 40, y * 40, h.getWidth(), h.getHeight());
    vipText tmp = h;
    toRender.push_back(tmp);
    r.push_back(x * 40);
    r.push_back(y * 40);
    posToRen.push_back(r);
    save.push_back(runner);
}

bool Play::pick(SDL_Renderer* ren, vector<int>& runner, vipText& green, int x, int y) {
    int row = y / 40 - 1;
    int coll = x / 40 - 1;
    for (int i = 0; i < runner.size(); i++) {
        if (runner[i] == row * 10 + coll) return false;
    }
    if (a[row][coll] != 0) return false;
    runner.push_back(row * 10 + coll);
    green.render(ren, 0, 0, (coll + 1) * 40, (row + 1) * 40, green.getWidth(), green.getHeight());
    SDL_RenderPresent(ren);
    return true;
}


	