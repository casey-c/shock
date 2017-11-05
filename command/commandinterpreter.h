#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

#include <QObject>
#include <QStack>
#include "icommand.h"

/*
 * The command interpreter is responsible for actually running commands. It
 * stores the undo and redo history.
 */
class CommandInterpreter : public QObject
{
    Q_OBJECT

public:
    CommandInterpreter() {}

    void run(ICommand* command);

    void undoLastCommand();
    void redoLastCommand();

signals:
    void updateUndoText(bool, QString);
    void updateRedoText(bool, QString);

private:
    QStack<ICommand*> undoStack;
    QStack<ICommand*> redoStack;

    void updateMenuText();
};

#endif // COMMANDINTERPRETER_H
