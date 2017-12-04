#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

#include <QObject>
#include <QStack>
#include "icommand.h"

/*
 * The command interpreter is responsible for actually running commands. It
 * stores the undo and redo history.
 *
 * This object is a singleton and can be altered with the static methods.
 */
class CommandInterpreter : public QObject
{
    Q_OBJECT

public:
    static CommandInterpreter& getInstance();

    void run(ICommand* command);

    void undoLastCommand();
    void redoLastCommand();

    CommandInterpreter(CommandInterpreter const&) = delete;
    void operator=(CommandInterpreter const&) = delete;

signals:
    void updateUndoText(bool, QString);
    void updateRedoText(bool, QString);

private:
    QStack<ICommand*> undoStack;
    QStack<ICommand*> redoStack;

    static CommandInterpreter* instance;

    CommandInterpreter() {}
    void updateMenuText();
};

#endif // COMMANDINTERPRETER_H
