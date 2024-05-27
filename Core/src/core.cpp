#include "core.h"
#include <qrandom.h>
#include <QObject>

//
//
// Bodyparts default
//
//
BodyPart::BodyPart(float chanceToHit, float costOfHitChance, bool killWhenHit) :
    m_chanceToHit(chanceToHit),
    m_costOfHitChance(costOfHitChance),
    m_killsWhenHit(killWhenHit)
{ }

BodyPart::BodyPart(float chanceToHit, float costOfHitChance, int livesOfPart) :
    m_chanceToHit(chanceToHit),
    m_costOfHitChance(costOfHitChance),
    m_livesOfPart(livesOfPart)
{ }

BodyPart::~BodyPart() = default;
//
//
// Bodyparts methods
//
//
float BodyPart::getChanceToHit() const { return m_chanceToHit; }

float BodyPart::getCostOfHitChance() const { return m_costOfHitChance; }

bool BodyPart::isImmobilized() const { return m_isImmobilized; }

int BodyPart::getLives() const { return m_livesOfPart; }

void BodyPart::setImmobilization(bool state) 
{
    m_isImmobilized = state;
}

void BodyPart::hit() 
{
    m_isImmobilized = true;
    if(m_killsWhenHit)
    {
        return;
    }
    if (m_livesOfPart >= 1)
        --m_livesOfPart;
}
//
//
// Head
//
//
Head::Head() : BodyPart(0.1, 0.0, true) {}

Head::~Head() = default;

QString Head::toString() const {
    if (isImmobilized())
	    return QString(QString("Секир башка"));
    return QString(QString("Голова на месте"));
}
//
//
// Leg
//
//
Leg::Leg() : BodyPart(0.2, 0.0, 2) {}
Leg::~Leg() = default;

QString Leg::toString() const {
    if (isImmobilized())
        return "Нога ранена! -30% шанс попадания";
	return "Нога на месте";
}
//
//
// Arm
//
//
Arm::Arm() : BodyPart(0.2, 0.5, 2) {}
Arm::~Arm() = default;

QString Arm::toString() const {
	if (m_isImmobilized)
        return "Рука ранена! -30% шанс попадания";
	return "Рука на месте";
}
//
//
// Body
//
//
Body::Body() : BodyPart(0.6, 0.1, 3) {}
Body::~Body() = default;

QString Body::toString() const {
	if (this->isImmobilized())
        return QString("Тело ранено! -") + QString::number(m_costOfHitChance * (3.0 - m_livesOfPart) * 100) + QString("% шанс попадания");
	return "Тело не похоже на тёрку";
}
//
//
// Duelist
//
//
Duelist::Duelist() = default;
Duelist::~Duelist() = default;

void Duelist::m_choicePartToHit() {
    auto result = QRandomGenerator64::global()->generateDouble();

    if (result < m_body.head.getChanceToHit())
    {
        m_isDead = true;
        return;
    }

    if (result < m_body.Lleg.getChanceToHit())
    {
        switch (QRandomGenerator64::global()->bounded(1,3))
        {
            case 1:
                m_body.Lleg.hit();
                break; 
            case 2:
                m_body.Rleg.hit();
                break;
            default:
                break;
        }
        return;
    }
    if (result < m_body.Larm.getChanceToHit())
    {
        switch (QRandomGenerator64::global()->bounded(1,3))
        {
            case 1:
                m_body.Larm.hit();
                break; 
            case 2:
                m_body.Rarm.hit();
                break;
            default:
                break;
        }
        return;
    }

    if (result < m_body.body.getChanceToHit())
    {
        // m_body
        // return;
    }
    
}

QStringList Duelist::toStringList() const {
    QStringList result;
    result.push_back(m_body.head.toString());
    result.push_back(m_body.body.toString());
    result.push_back(m_body.Larm.toString());
    result.push_back(m_body.Rarm.toString());
    result.push_back(m_body.Lleg.toString());
    result.push_back(m_body.Rleg.toString());
	return result;
}

bool Duelist::isDead() const {
	return m_isDead;
}

void Duelist::getHit() {

}

void Duelist::shoot() {
    m_isFired = true;
}

void Duelist::prepare() {
    m_isFired = false;
}

void Duelist::log(const QString &log) {
    m_logs.push_back(log);
}

QStringList Duelist::getLogs() const {
	return m_logs;
}
//
//
// Core
//
//
Core::Core() = default;

Core::~Core() = default;