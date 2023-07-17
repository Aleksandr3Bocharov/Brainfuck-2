// Copyright 2023 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2023-07-14
// https://github.com/Aleksandr3Bocharov/Brainfuck-2

/* 

Модуль "stdio" с реализацией на языке C функций для программ на языке программирования Рефал-05.
https://github.com/Mazdaywik/Refal-05

*/

#include <gtk\gtk.h>
#include <stdio.h>
#include "refal05rts.h"

/* 

<PutChar e.Char> ==

e.Char ::= s.CHAR? | s.CHAR e.ANY-EXPR

*/
R05_DEFINE_ENTRY_FUNCTION(PutChar, "PutChar") {
  struct r05_node *callee = arg_begin->next;
  struct r05_node *p;

#define CHECK_PUTCHAR(putchar_call) \
  ((putchar_call) != EOF ? (void) 0 \
  : r05_builtin_error_errno("Error in call " #putchar_call))
  
  p = callee->next;

  if ( p != arg_end)
    switch (p->tag)
    {
      case R05_DATATAG_CHAR:
        CHECK_PUTCHAR(putchar(p->info.char_));
        break;

      default:
        r05_switch_default_violation(p->tag);
    }

#undef CHECK_PUTCHAR

  r05_splice_to_freelist(arg_begin, arg_end);

}

/*

<GetChar> == s.Char

s.Char ::= s.CHAR

*/
R05_DEFINE_ENTRY_FUNCTION(GetChar, "GetChar") {
  struct r05_node *callee = arg_begin->next;

  if (callee->next != arg_end)
  {
    r05_recognition_impossible();
  }

  r05_reset_allocator();
  
  int cur_char = getchar();

  if (cur_char == EOF)
  {
    r05_alloc_number(0);
  }
  else
  {
    r05_alloc_char((char) cur_char);
  }

  r05_splice_from_freelist(arg_begin);
  r05_splice_to_freelist(arg_begin, arg_end);
}

/*

<OpenFileDialog> == e.bfFileName

e.bfFileName ::= s.CHAR*

*/
R05_DEFINE_ENTRY_FUNCTION(OpenFileDialog, "OpenFileDialog") {
  struct r05_node *callee = arg_begin->next;

  if (callee->next != arg_end)
  {
    r05_recognition_impossible();
  }

  r05_reset_allocator();

  gtk_init(0, NULL);

  GtkWidget *dialog;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;

  dialog = gtk_file_chooser_dialog_new("Открыть файл",
                                      NULL,
                                      action,
                                      ("Отмена"),
                                      GTK_RESPONSE_CANCEL,
                                      ("Открыть"),
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);

  res = gtk_dialog_run(GTK_DIALOG(dialog));
  if (res == GTK_RESPONSE_ACCEPT)
  {
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
    filename = gtk_file_chooser_get_filename(chooser); 
    r05_alloc_string(filename);
    g_free (filename);
  }  

  gtk_widget_destroy(dialog);

  r05_splice_from_freelist(arg_begin);
  r05_splice_to_freelist(arg_begin, arg_end);
}
