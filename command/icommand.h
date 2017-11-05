#ifndef ICOMMAND_H
#define ICOMMAND_H

#include<QString>

/*
 * This class serves as the interface for all undo-able or redo-able commands.
 *
 * Any action we deem important enough to undo or redo should derive this class
 * and implement all its pure virtual methods. Then, to actually run the
 * command, call:
 *
 *    CommandInterpreter.do( new DerivedCommand() )
 *
 *
 */
class ICommand
{
public:
    virtual bool act() = 0;
    virtual bool undo() = 0;

    bool redo() { return act(); }
    QString toString() const { return plainText; }

protected:
    QString plainText;
};

#endif // ICOMMAND_H
