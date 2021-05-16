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
    _ParticleControl->_fVelocity = 2.5;	 // ���l�����}�t��
    _ParticleControl->_fLifeTime = 3.5f;	 // ���l���s���ɶ�
    _ParticleControl->_fSpin = 0;
    _ParticleControl->_fOpacity = 255.0f;
    _ParticleControl->_fRed = 255.0f;
    _ParticleControl->_fGreen = 255.0f;
    _ParticleControl->_fBlue = 255.0f;
    _ParticleControl->_fGravity = 0;
    _ParticleControl->_fElpasedTime = 0;
    _ParticleControl->setType(STAY_FOR_TWOSECONDS); // ���l�B�ʪ����A�A�w�]�� 0
    _ParticleControl->_windDir = Point(0, 0); // ���d�ҨS����@�����\��
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

    // ���l���i�վ�Ѽƪ����ʶb
    auto* GravitySlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Gravity"));
    GravitySlider->addEventListener(CC_CALLBACK_2(CUIView::GravityEvent, this));
    GravitySlider->setMaxPercent(100); 	// �N 0 �� 100 ������ -10 �� 10 ����
    _GravityBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("GravityBMFont"));

    // Slider of Spread
    auto* SpreadSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Spread"));
    SpreadSlider->addEventListener(CC_CALLBACK_2(CUIView::SpreadEvent, this));
    SpreadSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 180 ����
    _SpreadBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("SpreadBMFont"));

    // Slider of Direction
    auto* DirectionSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Direction"));
    DirectionSlider->addEventListener(CC_CALLBACK_2(CUIView::DirectionEvent, this));
    DirectionSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 360 ����
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
    TypeSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 360 ����
    _TypeBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("TypeBMFont"));
}


void CUIView::onTouchBegan(const cocos2d::Point& tPoint)
{
    //��� Emitter �ɡA�i�즲�ӹϦ�
    if (_bEmitterOn) _EmitterSprite->touchesBegan(tPoint);

    // �S����� Emitter�A�ӥB�S�����b Emitter �������s�W�A�~�� touch �i�H�I����ܤ��l
    if (!_emitterSwitchBtn->touchesBegan(tPoint) && !_bEmitterOn) _ParticleControl->onTouchesBegan(tPoint);

}

void CUIView::onTouchMoved(const cocos2d::Point& tPoint)
{
    if (_bEmitterOn) {
        if (_EmitterSprite->touchesMoved(tPoint)) { // ���ʨç�s Emitter ����m
            _ParticleControl->_emitterPt = _EmitterSprite->getLoc();
        }
    }
    // �S����� Emitter�A�ӥB�S�����b Emitter �������s�W�A�~�� touch �i�H�I����ܤ��l
    if (!_emitterSwitchBtn->touchesMoved(tPoint) && !_bEmitterOn) _ParticleControl->onTouchesMoved(tPoint);
}

void CUIView::onTouchEnded(const cocos2d::Point& tPoint)
{
    if (_bEmitterOn) {
        if (_EmitterSprite->touchesEnded(tPoint)) {
            _ParticleControl->_emitterPt = _EmitterSprite->getLoc();
        }
    }
     // �I�b Emitter �������ϥܤW�A�i�楲�n�����A����
    if (_emitterSwitchBtn->touchesEnded(tPoint))
    {
        _bEmitterOn = _emitterSwitchBtn->getStatus();
        if (_bEmitterOn) { // ��� Emitter �ϥ�
            _EmitterSprite->setVisible(true);
        }
        else { // ���� Emitter �ϥ�
            _EmitterSprite->setVisible(false);
        }
        _ParticleControl->setEmitter(_bEmitterOn); // ��s����t�Τ��� Emitter ���A
    }

}

void CUIView::GravityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        float fGravity = (-50.0f + percent) / 5.0f; // �N 0 �� 100 ������ -10 �� 10 ����
        _GravityBMValue->setString(StringUtils::format("%2.1f", fGravity)); // �z�L _GravityBMValue ��ܦb�e���W
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
        float fSpread = percent * 1.8f; // 0 �� 180 ����
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
        float fDir = percent * 3.6f; // 0 �� 360 ����
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
        float fOpacity = percent * 2.55f; // 0 �� 255 ����
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
        int iParticle = percent * 2; // 0 �� 200 ����
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
        float fLifeTime = percent / 14.0f; // 0 �� 7 ����
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
        float fRed = percent * 2.55f; // 0 �� 255 ����
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
        float fGreen = percent * 2.55f; // 0 �� 255 ����
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
        float fBlue = percent * 2.55f; // 0 �� 255 ����
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
        int iType = percent / 20; // 0 �� 360 ����
        _TypeBMValue->setString(StringUtils::format("%2d", iType));
        _ParticleControl->setType(iType);
    }
}

