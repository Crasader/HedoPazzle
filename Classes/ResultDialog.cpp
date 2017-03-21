#include "ResultDialog.h"
#include "ui\CocosGUI.h"
#include "SelectScene.h"
#include "PlayScene.h"
#include "AudioEngine.h"
#include "TitleScene.h"
using namespace cocos2d;
// �T�v�F������
bool ResultDialog::init(bool result)
{
	if (!Node::init())
		return false;
	experimental::AudioEngine::stopAll();
	// ���̃��C���[���Â�����
	LayerColor* layerColor = LayerColor::create();
	layerColor->initWithColor(Color4B(0x00, 0x00, 0x00, 0xff));
	layerColor->setOpacity(100);
	this->addChild(layerColor);
	// ���̃��C���[�̃^�b�`��j�Q
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [&](Touch *touch, Event*event) {return true; };
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layerColor);
	// �_�C�A���O�摜
	Vec2 size = Director::getInstance()->getVisibleSize() / 2;
	Sprite* spr = Sprite::create();
	spr->setPosition(size);
	this->addChild(spr);
	if (result)
	{
		experimental::AudioEngine::play2d("result/clear1.mp3", true);
		experimental::AudioEngine::play2d("result/clear2.mp3");
		spr->setTexture("result/clear.png");
	}
	else
	{
		experimental::AudioEngine::play2d("result/over.mp3", true);
		spr->setTexture("result/over.png");
	}
	// �ĊJ�{�^��
	ui::Button* replay = ui::Button::create("result/replay.png");
	replay->setPosition(Vec2(115, 70));
	replay->addTouchEventListener([&](Ref* pRef, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED)return;
		experimental::AudioEngine::stopAll();
		experimental::AudioEngine::play2d("button.mp3");
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(PlayScene::createScene());
	});
	spr->addChild(replay);
	// �߂�{�^��
	ui::Button* back = ui::Button::create("result/back.png");
	back->setPosition(Vec2(285, 70));
	back->addTouchEventListener([&](Ref* pRef, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED)return;
		experimental::AudioEngine::stopAll();
		experimental::AudioEngine::play2d("button.mp3");
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(TitleScene::createScene());
	});
	spr->addChild(back);
	return true;
}

// �T�v�FResultDialog����
ResultDialog* ResultDialog::create(bool result)
{
	ResultDialog* pRet = new(std::nothrow)ResultDialog();
	if (pRet && pRet->init(result))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}
