#include "commandinterpreter.h"

/*
 * Run a command and if it is successful, add it to the undoStack and update
 * the menus accordingly.
 */
void CommandInterpreter::run(ICommand *command) {
    if (command->act()) {
        undoStack.push(command);

        // Note: this may need more complicated logic if any of our commands
        // utilize dynamic memory allocation: i.e. we may need to cleanup
        // memory leaks
        redoStack.clear();

        updateMenuText();
    }
}

/*
 * Undo the last command, if applicable
 */
void CommandInterpreter::undoLastCommand() {
    if (undoStack.empty())
        return;

    ICommand* last = undoStack.pop();
    last->undo();
    redoStack.push(last);

    updateMenuText();
}

/*
 * Redo the last command undo-ed, if applicable
 */
void CommandInterpreter::redoLastCommand() {
    if (redoStack.empty())
        return;

    ICommand* last = redoStack.pop();
    last->redo();
    undoStack.push(last);

    updateMenuText();
}

/*
 * Send out signals with the updated undo/redo menu text. The first argument
 * in the signal is a bool signifying whether or not the undo/redo option
 * should be enabled (i.e. whether anything is left to undo or redo)
 */
void CommandInterpreter::updateMenuText() {
    if (undoStack.empty())
        emit updateUndoText(false, "Undo");
    else
        emit updateUndoText(true, "Undo: " + undoStack.top()->toString());

    if (redoStack.empty())
        emit updateRedoText(false, "Redo");
    else
        emit updateRedoText(true, "Redo: " + redoStack.top()->toString());
}
