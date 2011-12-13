/*
 * Copyright (C) 2007 Kevin Ollivier <kevino@theolliviers.com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "config.h"
#include "EditorClientHl.h"

#include "EditCommand.h"
#include "Editor.h"
#include "FocusController.h"
#include "Frame.h"
#include "FrameView.h"
#include "HostWindow.h"
#include "KeyboardEvent.h"
#include "WindowsKeyboardCodes.h"
#include "NotImplemented.h"
#include "Page.h"
#include "PlatformKeyboardEvent.h"
#include "PlatformString.h"

#include <stdio.h>

namespace WebCore {

EditorClientHl::~EditorClientHl()
{
    m_page = NULL;
}

void EditorClientHl::setPage(Page* page)
{
    m_page = page;
}

void EditorClientHl::pageDestroyed()
{
    delete this;
}

bool EditorClientHl::shouldDeleteRange(Range*)
{
    notImplemented();
    return true;
}

bool EditorClientHl::shouldShowDeleteInterface(HTMLElement*)
{
    notImplemented();
    return false;
}

bool EditorClientHl::smartInsertDeleteEnabled()
{
    notImplemented();
    return false;
}

bool EditorClientHl::isSelectTrailingWhitespaceEnabled()
{
    notImplemented();
    return false;
}

bool EditorClientHl::isContinuousSpellCheckingEnabled()
{
    notImplemented();
    return false;
}

void EditorClientHl::toggleContinuousSpellChecking()
{
    notImplemented();
}

bool EditorClientHl::isGrammarCheckingEnabled()
{
    notImplemented();
    return false;
}

void EditorClientHl::toggleGrammarChecking()
{
    notImplemented();
}

int EditorClientHl::spellCheckerDocumentTag()
{
    notImplemented();
    return 0;
}

bool EditorClientHl::selectWordBeforeMenuEvent()
{
    notImplemented();
    return false;
}

bool EditorClientHl::isEditable()
{
    return true;
}

bool EditorClientHl::shouldBeginEditing(Range*)
{
    notImplemented();
    return true;
}

bool EditorClientHl::shouldEndEditing(Range*)
{
    notImplemented();
    return true;
}

bool EditorClientHl::shouldInsertNode(Node*, Range*,
                                       EditorInsertAction)
{
    notImplemented();
    return true;
}

bool EditorClientHl::shouldInsertText(const String&, Range*,
                                       EditorInsertAction)
{
    notImplemented();
    return true;
}

bool EditorClientHl::shouldApplyStyle(CSSStyleDeclaration*,
                                       Range*)
{
    notImplemented();
    return true;
}

bool EditorClientHl::shouldMoveRangeAfterDelete(Range*, Range*)
{
    notImplemented();
    return true;
}

bool EditorClientHl::shouldChangeSelectedRange(Range* fromRange, Range* toRange, 
                                EAffinity, bool stillSelecting)
{
    notImplemented();
    return true;
}

void EditorClientHl::didBeginEditing()
{
    notImplemented();
}

void EditorClientHl::respondToChangedContents()
{
    notImplemented();
}

void EditorClientHl::didEndEditing()
{
    notImplemented();
}

void EditorClientHl::didWriteSelectionToPasteboard()
{
    notImplemented();
}

void EditorClientHl::didSetSelectionTypesForPasteboard()
{
    notImplemented();
}

void EditorClientHl::registerCommandForUndo(PassRefPtr<EditCommand> command)
{
}

void EditorClientHl::registerCommandForRedo(PassRefPtr<EditCommand> command)
{
}

void EditorClientHl::clearUndoRedoOperations()
{
}

bool EditorClientHl::canCopyCut(Frame*, bool defaultValue) const
{
    return defaultValue;
}

bool EditorClientHl::canPaste(Frame*, bool defaultValue) const
{
    return defaultValue;
}

bool EditorClientHl::canUndo() const
{
    return false;
}

bool EditorClientHl::canRedo() const
{
    return false;
}

void EditorClientHl::undo()
{
}

void EditorClientHl::redo()
{
}

bool EditorClientHl::handleEditingKeyboardEvent(KeyboardEvent* event)
{
    return false;
}

const char* EditorClientHl::interpretKeyEvent(const KeyboardEvent* evt)
{
    return 0;
}


void EditorClientHl::handleInputMethodKeydown(KeyboardEvent* event)
{
// NOTE: we don't currently need to handle this. When key events occur,
// both this method and handleKeyboardEvent get a chance at handling them.
// We might use this method later on for IME-specific handling.
}

void EditorClientHl::handleKeyboardEvent(KeyboardEvent* event)
{
    Frame *frame = event->target()->toNode()->document()->frame();

    if (!frame || !frame->document()->focusedNode())
        return;

    if (event->defaultPrevented())
        return;

    const PlatformKeyboardEvent* kevent = event->keyEvent();
    if (!kevent || kevent->type() != PlatformKeyboardEvent::Char) {
        return;
    }

    String cmd;
    switch(kevent->windowsVirtualKeyCode()) {
        case VK_BACK:
            cmd = "DeleteBackward";
            break;
        case VK_PRIOR:
            cmd = "MovePageUp";
            break;
        case VK_NEXT:
            cmd = "MovePageDown";
            break;
        case VK_END:
            cmd = "MoveToEndOfLine";
            break;
        case VK_HOME:
            cmd = "MoveToBeginningOfLine";
            break;
        case VK_LEFT:
            cmd = "MoveLeft";
            break;
        case VK_UP:
            cmd = "MoveUp";
            break;
        case VK_RIGHT:
            cmd = "MoveRight";
            break;
        case VK_DOWN:
            cmd = "MoveDown";
            break;
        case VK_DELETE:
            cmd = "DeleteForward";
            break;
    }
    if (event->ctrlKey()) {
        switch(event->charCode()) {
            case 'x': 
                cmd = "Cut";
                break;
            case 'c': 
                cmd = "Copy";
                break;
            case 'v': 
                cmd = "Paste";
                break;
            case 'a': 
                cmd = "SelectAll";
                break;
        }
    }
    /* If shift modifier is used, and action it to move a cursor - modify selection as well */
    if (event->shiftKey() && cmd.startsWith("Move")) {
        cmd.append("AndModifySelection");
    }
    if (!cmd.isEmpty()) {
        frame->editor()->command(cmd).execute(event);
        return;
    } else if (event->charCode()) {
        frame->editor()->insertText(kevent->text(), event);
        return;
    }

    event->setDefaultHandled();
}

void EditorClientHl::textFieldDidBeginEditing(Element*)
{
    notImplemented();
}

void EditorClientHl::textFieldDidEndEditing(Element*)
{
    notImplemented();
}

void EditorClientHl::textDidChangeInTextField(Element*)
{
    notImplemented();
}

bool EditorClientHl::doTextFieldCommandFromEvent(Element*, KeyboardEvent*)
{
    notImplemented();
    return false;
}

void EditorClientHl::textWillBeDeletedInTextField(Element*)
{
    notImplemented();
}

void EditorClientHl::textDidChangeInTextArea(Element*)
{
    notImplemented();
}

void EditorClientHl::respondToChangedSelection(Frame*)
{
    notImplemented();
}

void EditorClientHl::ignoreWordInSpellDocument(const String&) 
{ 
    notImplemented(); 
}

void EditorClientHl::learnWord(const String&) 
{ 
    notImplemented(); 
}

void EditorClientHl::checkSpellingOfString(const UChar*, int length, int* misspellingLocation, int* misspellingLength) 
{ 
    notImplemented(); 
}

void EditorClientHl::checkGrammarOfString(const UChar*, int length, Vector<GrammarDetail>&, int* badGrammarLocation, int* badGrammarLength) 
{ 
    notImplemented(); 
}

void EditorClientHl::updateSpellingUIWithGrammarString(const String&, const GrammarDetail& detail) 
{ 
    notImplemented(); 
}

void EditorClientHl::updateSpellingUIWithMisspelledWord(const String&) 
{ 
    notImplemented(); 
}

void EditorClientHl::showSpellingUI(bool show) 
{ 
    notImplemented(); 
}

bool EditorClientHl::spellingUIIsShowing() 
{ 
    notImplemented(); 
    return false;
}

void EditorClientHl::getGuessesForWord(const String&, const String&, Vector<String>& guesses) 
{ 
    notImplemented(); 
}

String EditorClientHl::getAutoCorrectSuggestionForMisspelledWord(const String&)
{
    notImplemented();
    return String();
}

void EditorClientHl::willSetInputMethodState()
{
    notImplemented();
}

void EditorClientHl::setInputMethodState(bool enabled)
{
    notImplemented();
}

}
