#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "filesys/file.h"
#include "filesys/filesys.h"

static void syscall_handler (struct intr_frame *);


struct fide {
  struct file *file_struct;
  int fd;
};

void
syscall_init (void)
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED)
{
   //printf("syscall : %d\n", *(uint32_t *)(f->esp));
   //hex_dump(f->esp, f->esp, 100, 1);
   switch (*(uint32_t *)(f->esp)) {
    case SYS_HALT:
      break;
    case SYS_EXIT:
      exit(*(uint32_t *)(f->esp + 4));
      break;
    case SYS_EXEC:
      break;
    case SYS_WAIT:
      break;
    case SYS_CREATE:
      break;
    case SYS_REMOVE:
      break;
    case SYS_OPEN:
      break;
    case SYS_FILESIZE:
      break;
    case SYS_READ:
      break;
    case SYS_WRITE:
       f->eax = write((int)*(uint32_t *)(f->esp+4), (void *)*(uint32_t *)(f->esp + 8),(unsigned)*((uint32_t *)(f->esp + 12)));
      break;
    case SYS_SEEK:
      break;
    case SYS_TELL:
      break;
    case SYS_CLOSE:
      break;
  }

}
void halt (void) {
  shutdown_power_off();
}

void exit (int status) {
  printf("%s: exit(%d)\n", thread_name(), status);
  thread_exit ();
}

pid_t exec (const char *cmd_line) {
  return process_execute(cmd_line);
}

int wait (pid_t pid) {
  return process_wait(pid);
}

int read (int fd, void* buffer, unsigned size) {
  int i;
  if (fd == 0) {
    for (i = 0; i < size; i ++) {
      if (((char *)buffer)[i] == '\0') {
        break;
      }
    }
  }
  return i;
}

bool create (const char *file, unsigned initial_size){
  return filesys_create(file, initial_size);
}

int write (int fd, const void *buffer, unsigned size) {
  if (fd == 1) {
    putbuf(buffer, size);
    return size;
  }
  return -1;
}
