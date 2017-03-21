#include "TitleScene.h"
#include "SelectScene.h"
#include "PlayScene.h"
#include "Hedoro.h"
#include "AudioEngine.h"
using namespace cocos2d;
bool TitleScene::init()
{
	if (!Layer::init())
		return false;
	experimental::AudioEngine::play2d("title/BGM.mp3", true);
	Sprite* spr = Sprite::create("title/back.png");
	spr->setPosition(250, 400);
	this->addChild(spr);
	Sprite* title = Sprite::create("title/title.png");
	title->setPosition(250, 500);
	this->addChild(title,100);
	Label* label = Label::create("Tap to Start", "Arial", 50);
	label->setPosition(250.0f, 100.0f);
	label->setColor(Color3B::BLACK);
	this->addChild(label,100);
	FadeTo* fade1 = FadeTo::create(1, 255);
	FadeTo* fade2 = FadeTo::create(1, 100);
	ScaleTo* scale1 = ScaleTo::create(1, 1.5f);
	ScaleTo* scale2 = ScaleTo::create(1, 1);
	Sequence* seq1 = Sequence::create(fade1, fade2, nullptr);
	Sequence* seq2 = Sequence::create(scale1, scale2, nullptr);
	Spawn* spawn = Spawn::create(seq1, seq2, nullptr);
	RepeatForever* repeat = RepeatForever::create(spawn);
	label->runAction(repeat);
	// タッチ有効化
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	scheduleUpdate();
	return true;
}

void TitleScene::update(float delta)
{
	static int time;
	time++;
	if (time > 20)
	{
		Hedoro* hedoro = Hedoro::create();
		int x = random(50, 450);
		hedoro->setPosition(x, 800);
		this->addChild(hedoro);
		x = random(0, 500);
		int y = random(-100, 0);
		MoveTo* move = MoveTo::create(2, Vec2(x, y));
		int angle = random(-180, 180);
		RotateBy* rota = RotateBy::create(2, angle);
		Spawn* spawn = Spawn::create(move, rota, nullptr);
		RemoveSelf* re = RemoveSelf::create();
		Sequence* seq = Sequence::create(spawn, re, nullptr);
		hedoro->runAction(seq);
		time = 0;
	}
	m_touchTime++;
}

bool TitleScene::onTouchBegan(Touch * touch,Event * event)
{
	m_touchTime = 0;
	return true;
}

void TitleScene::onTouchMoved(Touch * touch,Event * event)
{
}

void TitleScene::onTouchEnded(Touch * touch,Event * event)
{
	if (m_touchTime <= 80)
	{
		experimental::AudioEngine::stopAll();
		experimental::AudioEngine::play2d("button.mp3");
		Director::getInstance()->replaceScene(
			PlayScene::createScene());
	}
}

Scene * TitleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TitleScene::create();
	scene->addChild(layer);
	return scene;
}
