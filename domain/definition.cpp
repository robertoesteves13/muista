#include "definition.hpp"

Definition::Definition(QObject *parent, QString pMeaning, QString pObservation)
    : QObject(parent) {
    this->m_meaning = pMeaning;
    this->m_observation = pObservation;
}

Definition::~Definition() {}

