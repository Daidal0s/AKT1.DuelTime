#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QStringList>

class BodyPart {
protected:
	bool m_killsWhenHit = false;
	int m_livesOfPart = 1;
	bool m_isImmobilized = false;
	float m_chanceToHit /*= 0.0*/;
	float m_costOfHitChance /*= 0.0*/;

public:
	BodyPart(float chanceToHit, float costOfHitChance, bool killWhenHit);
	BodyPart(float chanceToHit, float costOfHitChance, int livesOfPart);
	virtual ~BodyPart();

	float getChanceToHit() const;
	float getCostOfHitChance() const;
	bool isImmobilized() const;

	int getLives() const;

	void setImmobilization(bool state);
	void hit();

	virtual QString toString() const = 0;
};

class Head : public BodyPart {
public:
	Head();
	~Head() override;

	QString toString() const override;
};

class Leg : public BodyPart {
public:
	Leg();
	~Leg() override;

	QString toString() const override;
};

class Arm : public BodyPart {
public:
	Arm();
	~Arm() override;

	QString toString() const override;
};

class Body : public BodyPart {
public:
	Body();
	~Body() override;

	QString toString() const override;
};

struct DuelistsBody {
public:
	Head head;
	Body body;
	Arm Larm;
	Arm Rarm;
	Leg Lleg;
	Leg Rleg;
};

class Duelist
{
private:
	bool m_isDead = false;
	bool m_isFired = false;
	float m_chanceToWin = 1.0;
	DuelistsBody m_body;
	QStringList m_logs;

	void m_choicePartToHit();
public:
	Duelist();
	~Duelist();

	QStringList toStringList() const;
	
	bool isDead() const;

	void getHit();
	void prepare();
	void shoot();

	void log(const QString &log);
	QStringList getLogs() const;
};

class Core {
private:
	QList<Duelist> m_duelists;
	QList<Duelist> m_liveDuelists;
	QList<Duelist> m_deadDuelists;
	QList<Duelist> m_pickedDuelists;

public:
	Core();
	~Core();
};

#endif	// CORE_H
