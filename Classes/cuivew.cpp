#include "cuiview.h"

using namespace cocos2d::ui;

USING_NS_CC;

extern cocos2d::Size fSize;

CUIView::CUIView()
{
	_uiRoot = nullptr;
    _stage = nullptr;
    _ParticleControl = nullptr;
    _GravityBMValue = nullptr;
    _SpreadBMValue = nullptr;
    _DirectionBMValue = nullptr;
    _SpinBMValue = nullptr;
    _SpeedBMValue = nullptr;
    _OpacityBMValue = nullptr;
    _ParticleBMValue = nullptr;
    _LifeTimeBMValue = nullptr;
    _RedBMValue = nullptr;
    _GreenBMValue = nullptr;
    _BlueBMValue = nullptr;
    _TypeBMValue = nullptr;
    _EmitterSprite = nullptr;
    _emitterSwitchBtn = nullptr;
    _bEmitterOn = false;
}

void CUIView::setModel(CParticleSystem& model)
{
    _ParticleControl = &model;
    _ParticleControl->init(*_stage);
    _ParticleControl->_emitterPt = _EmitterSprite->getLoc();
    _ParticleControl->_fDir = 90.0;
    _ParticleControl->_iNumParticles = 100;
    _ParticleControl->_iGenParticles = 0;
    _ParticleControl->_fSpread = 180.0f;
    _ParticleControl->_fVelocity = 2.5;	 // 分子的離開速度
    _ParticleControl->_fLifeTime = 3.5f;	 // 分子的存活時間
    _ParticleControl->_fSpin = 0;
    _ParticleControl->_fOpacity = 255.0f;
    _ParticleControl->_fRed = 255.0f;
    _ParticleControl->_fGreen = 255.0f;
    _ParticleControl->_fBlue = 255.0f;
    _ParticleControl->_fGravity = 0;
    _ParticleControl->_fElpasedTime = 0;
    _ParticleControl->setType(STAY_FOR_TWOSECONDS); // 分子運動的型態，預設為 0
    _ParticleControl->_windDir = Point(0, 0); // 本範例沒有實作此項功能
}

void CUIView::setProperty(std::string uicsbname, cocos2d::Size vsize, cocos2d::Scene& stage)
{
	_uiRoot = CSLoader::createNode(uicsbname);
	stage.addChild(_uiRoot);
	_uiRoot->setPosition(Vec2(0,0));
    _stage = &stage;
    _size = vsize;
    init();
}

void CUIView::init() 
{
    // For Emitter
    _EmitterSprite = CDraggableSprite::create();
    _EmitterSprite->setSpriteInfo("emittericon.png", Point(-125.0f + _size.width / 2.0f, _size.height / 2.0f));
    _EmitterSprite->setVisible(false);
    _bEmitterOn = false;
    _stage->addChild(_EmitterSprite, 5);

    auto emiterpos = dynamic_cast<Sprite*>(_uiRoot->getChildByName("emitterpos"));
    Point loc = emiterpos->getPosition();
    emiterpos->setVisible(false);
    _emitterSwitchBtn = CSwitchButton::create();
    _emitterSwitchBtn->setButtonInfo("emitteroff.png", "emitteron.png", "emittertd.png", loc);
    _stage->addChild(_emitterSwitchBtn, 2);

    // 分子的可調整參數的捲動軸
    auto* GravitySlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Gravity"));
    GravitySlider->addEventListener(CC_CALLBACK_2(CUIView::GravityEvent, this));
    GravitySlider->setMaxPercent(100); 	// 將 0 到 100 對應到 -10 到 10 之間
    _GravityBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("GravityBMFont"));

    // Slider of Spread
    auto* SpreadSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Spread"));
    SpreadSlider->addEventListener(CC_CALLBACK_2(CUIView::SpreadEvent, this));
    SpreadSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 180 之間
    _SpreadBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("SpreadBMFont"));

    // Slider of Direction
    auto* DirectionSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Direction"));
    DirectionSlider->addEventListener(CC_CALLBACK_2(CUIView::DirectionEvent, this));
    DirectionSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
    _DirectionBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("DirectionBMFont"));

    //Slider of Spin
    auto* SpinSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Spin"));
    SpinSlider->addEventListener(CC_CALLBACK_2(CUIView::SpinEvent, this));
    SpinSlider->setMaxPercent(100);
    _SpinBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("SpinBMFont"));

    //Slider of Opacity
    auto* OpacitySlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Opacity"));
    OpacitySlider->addEventListener(CC_CALLBACK_2(CUIView::OpacityEvent, this));
    OpacitySlider->setMaxPercent(100);
    _OpacityBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("OpacityBMFont"));

    //Slider of Particle
    auto* ParticleSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Particles"));
    ParticleSlider->addEventListener(CC_CALLBACK_2(CUIView::ParticleEvent, this));
    ParticleSlider->setMaxPercent(100);
    _ParticleBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("ParticlesBMFont"));

    //Slider of LifeTime
    auto* LifeTimeSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Lifetime"));
    LifeTimeSlider->addEventListener(CC_CALLBACK_2(CUIView::LifeTimeEvent, this));
    LifeTimeSlider->setMaxPercent(100);
    _LifeTimeBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("LifetimeBMFont"));

    //Slider of Red
    auto* RedSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Red"));
    RedSlider->addEventListener(CC_CALLBACK_2(CUIView::RedEvent, this));
    RedSlider->setMaxPercent(100);
    _RedBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("RedBMFont"));

    //Slider of Green
    auto* GreenSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Green"));
    GreenSlider->addEventListener(CC_CALLBACK_2(CUIView::GreenEvent, this));
    GreenSlider->setMaxPercent(100);
    _GreenBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("GreenBMFont"));

    //Slider of Blue
    auto* BlueSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Blue"));
    BlueSlider->addEventListener(CC_CALLBACK_2(CUIView::BlueEvent, this));
    BlueSlider->setMaxPercent(100);
    _BlueBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("BlueBMFont"));

    //Slider of Speed
    auto* SpeedSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Speed"));
    SpeedSlider->addEventListener(CC_CALLBACK_2(CUIView::SpeedEvent, this));
    SpeedSlider->setMaxPercent(100);
    _SpeedBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("SpeedBMFont"));

    // Slider of Type
    auto* TypeSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Type"));
    TypeSlider->addEventListener(CC_CALLBACK_2(CUIView::TypeEvent, this));
    TypeSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
    _TypeBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("TypeBMFont"));
}


void CUIView::onTouchBegan(const cocos2d::Point& tPoint)
{
    //顯示 Emitter 時，可拖曳該圖式
    if (_bEmitterOn) _EmitterSprite->touchesBegan(tPoint);

    // 沒有顯示 Emitter，而且沒有按在 Emitter 切換按鈕上，才讓 touch 可以點選顯示分子
    if (!_emitterSwitchBtn->touchesBegan(tPoint) && !_bEmitterOn) _ParticleControl->onTouchesBegan(tPoint);

}

void CUIView::onTouchMoved(const cocos2d::Point& tPoint)
{
    if (_bEmitterOn) {
        if (_EmitterSprite->touchesMoved(tPoint)) { // 移動並更新 Emitter 的位置
            _ParticleControl->_emitterPt = _EmitterSprite->getLoc();
        }
    }
    // 沒有顯示 Emitter，而且沒有按在 Emitter 切換按鈕上，才讓 touch 可以點選顯示分子
    if (!_emitterSwitchBtn->touchesMoved(tPoint) && !_bEmitterOn) _ParticleControl->onTouchesMoved(tPoint);
}

void CUIView::onTouchEnded(const cocos2d::Point& tPoint)
{
    if (_bEmitterOn) {
        if (_EmitterSprite->touchesEnded(tPoint)) {
            _ParticleControl->_emitterPt = _EmitterSprite->getLoc();
        }
    }
     // 點在 Emitter 切換的圖示上，進行必要的狀態改變
    if (_emitterSwitchBtn->touchesEnded(tPoint))
    {
        _bEmitterOn = _emitterSwitchBtn->getStatus();
        if (_bEmitterOn) { // 顯示 Emitter 圖示
            _EmitterSprite->setVisible(true);
        }
        else { // 關閉 Emitter 圖示
            _EmitterSprite->setVisible(false);
        }
        _ParticleControl->setEmitter(_bEmitterOn); // 更新控制系統中的 Emitter 狀態
    }

}

void CUIView::GravityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        float fGravity = (-50.0f + percent) / 5.0f; // 將 0 到 100 對應到 -10 到 10 之間
        _GravityBMValue->setString(StringUtils::format("%2.1f", fGravity)); // 透過 _GravityBMValue 顯示在畫面上
        _ParticleControl->setGravity(fGravity);
    }
}

void CUIView::SpreadEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        float fSpread = percent * 1.8f; // 0 到 180 之間
        _SpreadBMValue->setString(StringUtils::format("%2.1f", fSpread));
        _ParticleControl->_fSpread = fSpread;
    }
}

void CUIView::DirectionEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        float fDir = percent * 3.6f; // 0 到 360 之間
        _DirectionBMValue->setString(StringUtils::format("%2.1f", fDir));
        _ParticleControl->_fDir = fDir;
    }
}

void CUIView::OpacityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        float fOpacity = percent * 2.55f; // 0 到 255 之間
        _OpacityBMValue->setString(StringUtils::format("%2.1f", fOpacity));
        _ParticleControl->_fOpacity = fOpacity;
    }
}

void CUIView::ParticleEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        int iParticle = percent * 2; // 0 到 200 之間
        _ParticleBMValue->setString(StringUtils::format("%d", iParticle));
        _ParticleControl->_iNumParticles = iParticle;
    }
}

void CUIView::LifeTimeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        float fLifeTime = percent / 14.0f; // 0 到 7 之間
        _LifeTimeBMValue->setString(StringUtils::format("%2.1f", fLifeTime));
        _ParticleControl->_fLifeTime = fLifeTime;
    }
}

void CUIView::RedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        float fRed = percent * 2.55f; // 0 到 255 之間
        _RedBMValue->setString(StringUtils::format("%2.1f", fRed));
        _ParticleControl->_fRed = fRed;
    }
}

void CUIView::GreenEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        float fGreen = percent * 2.55f; // 0 到 255 之間
        _GreenBMValue->setString(StringUtils::format("%2.1f", fGreen));
        _ParticleControl->_fGreen = fGreen;
    }
}

void CUIView::BlueEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        float fBlue = percent * 2.55f; // 0 到 255 之間
        _BlueBMValue->setString(StringUtils::format("%2.1f", fBlue));
        _ParticleControl->_fBlue = fBlue;
    }
}

void CUIView::SpinEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        float fSpin = percent * 1.8f;
        _SpinBMValue->setString(StringUtils::format("%2.1f", fSpin));
        _ParticleControl->_fSpin = fSpin;
    }
}

void CUIView::SpeedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        float fSpeed = percent / 2.5f;
        _SpeedBMValue->setString(StringUtils::format("%2.1f", fSpeed));
        _ParticleControl->setSpeed(fSpeed);
    }
}


void CUIView::TypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        int iType = percent / 20; // 0 到 360 之間
        _TypeBMValue->setString(StringUtils::format("%2d", iType));
        _ParticleControl->setType(iType);
    }
}

