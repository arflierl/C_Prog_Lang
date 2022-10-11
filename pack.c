#include <stdlib.h>
#include <string.h>

#include "serialize.h"



/* Pack the user input provided in input into the appropriate message
 * type in the space provided by packed.  You can assume that input is a
 * NUL-terminated string, and that packed is a buffer of size
 * PACKET_SIZE.
 *
 * Returns the message type for valid input, or -1 for invalid input.
 */
int pack(void *packed, char *input) {
  if (*(input) == '/') {
    //status or statistics
    //returns STATUS or STATISTICS

    

    //status
    if (*(input + 1) == 'm') {
      char *check = "/me ";
      char *test = input;//check that input begins with "/me " for any status
      for (int i = 0; i < 4; i++) {
	if (*(check + i) != *(test + i)) { 
	  return -1; //return error if invalid status
	}
      }
      
      
      //enter the data for the Status Packet
      
      void *status_packer = packed;
      *(int *)status_packer = STATUS;
      
      status_packer += sizeof(int);//move this pointer along by sizeof(int) bytes (4)
      
      char *name = "arflierl";//my UBID

      int ub_ID_chars = 0;
      for (int i = 0; i < 8; i++) {
	*(char *)status_packer = *(name + i);//entering my UBID
	if (*(char *)status_packer != ' ') {
	  ub_ID_chars++;
	}
	status_packer++;
      }

      if (ub_ID_chars == 0) {
	return -1; //UBID is only whitespace
      }
      
      for (int i = 8; i < NAME_SIZE; i++) {
	*(char *)status_packer = '\0';//padding the remaining NAME_SIZE bytes with ASCII NULL
	status_packer++;
      }
      
      char *status_text = (input + 4);
      while(*(status_text) == ' ') {
	status_text++;
      }
      
      char *counter = status_text;
      size_t strlen = 0;
      int realMSG = 0; //input is not all white-space
      while(*(counter) != '\0') {
	strlen++;
	if (*(counter) != ' ') {
	  realMSG++;
	}
	counter++;
      }
      
      if (realMSG == 0) {
	return -1; //if message is all whitespace, return error
      }

      if (strlen > MAX_MESSAGE_SIZE) {
	return -1;
      }

      if (strlen == 0) {
	return -1; //if strlen == 0 this is an invalid status
      }
      
      //strlen is the length of the entered input
      
      
      *(size_t *)status_packer = strlen;
      
      status_packer += sizeof(size_t);
      
      *(size_t *)status_packer = 0;
      
      status_packer += sizeof(size_t);
      
      while (*(status_text) != '\0') {
	*(char *)status_packer = *(status_text);
	status_packer++;
	status_text++;
      }
      
      *(char *)status_packer = '\0';
      
      
      
      
      return STATUS;
      
    }

    if (*(input + 1) == 's') {
      char *stats_test = "/stats";
      char *stats_text = input;
      while (*(stats_test) != '\0') {
	if (*(stats_text) != *(stats_test)) {
	  //not a valid input for stats
	  return -1;
	}
	stats_text++;
	stats_test++;
      }
    

      if (*(stats_text) != ' ' && *(stats_text) != '\0') {
	//input is not of form "/stats" or "/stats ....."
	return -1;
      }
      
      //I now know that this is a valid input for a stats packet
      
      void *stats_packer = packed;
      *(int *)stats_packer = STATISTICS;
      
      stats_packer += sizeof(int);//move this pointer along by sizeof(int) bytes (4)
      
      char *name = "arflierl";//my UBID

      int UBID_chars = 0;
      for (int i = 0; i < 8; i++) {
	*(char *)stats_packer = *(name + i);//entering my UBID
	if (*(name + i) != ' ') {
	  UBID_chars++;
	}
	stats_packer++;
      }

      if (UBID_chars == 0) {
	return -1;
      }
      
      for (int i = 8; i < NAME_SIZE; i++) {
	*(char *)stats_packer = '\0';//padding the remaining NAME_SIZE bytes with ASCII NULL
	stats_packer++;
      }
      
      return STATISTICS;
    } 
  }
  
  if (*(input) == '@') {
    //LABELED
    input++;
    char *test_tag = input;
    size_t target_length = 0;
    while (*(test_tag) != ' ' && *(test_tag) != '\0') {
      target_length++;
      test_tag++;
    }

    if (target_length > NAME_SIZE) {
      return -1; //if the target_length is larger than the allowed length, it is invalid
    }

    size_t msg_length = 0;
    size_t whitespace = 0;

    while (*(test_tag) == ' ') {
      whitespace++;
      test_tag++;
    }

    if (*(test_tag) != '\0') {
      while (*(test_tag) != '\0') {
	msg_length++;
	test_tag++;
      }
    }

    size_t input_length = target_length + whitespace + msg_length;

    if ((target_length + msg_length) > MAX_MESSAGE_SIZE) {
      return -1;
    }

    void *labeled_packer = packed;

    *(int *)labeled_packer = LABELED;
    
    labeled_packer += sizeof(int);//move this pointer along by sizeof(int) bytes (4)
    
    char *name = "arflierl";//my UBID
    
    for (int i = 0; i < 8; i++) {
      *(char *)labeled_packer = *(name + i);//entering my UBID
      labeled_packer++;
    }
    
    for (int i = 8; i < NAME_SIZE; i++) {
      *(char *)labeled_packer = '\0';//padding the remaining NAME_SIZE bytes with ASCII NULL
      labeled_packer++;
    }

    *(size_t *)labeled_packer = msg_length;

    labeled_packer += sizeof(size_t);

    *(size_t *)labeled_packer = target_length;

    labeled_packer += sizeof(size_t);

    *(size_t *)labeled_packer = 0;

    labeled_packer += sizeof(size_t);

    int labeled_msg_chars = 0;
    
    for (int i = target_length + whitespace; i < input_length; i++) {
      *(char *)labeled_packer = *(input + i);
      if (*(char *)labeled_packer != ' ') {
	labeled_msg_chars++;
      }
      labeled_packer++;
    }

    if (labeled_msg_chars == 0) {
      return -1; //whitespace msg is invalid
    }

    int target_chars = 0;
    
    for (int i = 0; i < target_length; i++) {
      *(char *)labeled_packer = *(input + i);
      if (*(char *)labeled_packer != ' ') {
	target_chars++;
      }
      labeled_packer++;
    }

    if (target_chars == 0) {
      return -1; //whitespace target is invalid
    }

 
    return LABELED;
  }

  //now I know that the input type is either a message or invalid
  void *message_packer = packed;
  *(int *)message_packer = MESSAGE;


  message_packer += sizeof(int);//move this pointer along by sizeof(int) bytes (4)
  
  char *name = "arflierl";//my UBID
  
  for (int i = 0; i < 8; i++) {
    *(char *)message_packer = *(name + i);//entering my UBID
    message_packer++;
  }
  
  for (int i = 8; i < NAME_SIZE; i++) {
    *(char *)message_packer = '\0';//padding the remaining NAME_SIZE bytes with ASCII NULL
    message_packer++;
    }

  char *counter = input;
  size_t strlen = 0;
  int realMSG = 0; //input is not all white-space
  while(*(counter) != '\0') {
    strlen++;
    if (*(counter) != ' ') {
      realMSG++;
    }
    counter++;
  }

  if (strlen > MAX_MESSAGE_SIZE) {
    return -1; //if message is too long, return error
  }

  if(realMSG == 0) {
    return -1; //if message is all whitespace, return error
  }
  //strlen is the length of the entered input
  

  *(size_t *)message_packer = strlen;
  
  message_packer += sizeof(size_t);

  *(size_t *)message_packer = 0;

  message_packer += sizeof(size_t);

  for (int i = 0; i < strlen; i++) {
    *(char *)message_packer = *input;
    input +=1;
    message_packer++;
  }
  
  *(char *)message_packer = '\0';
  
  return MESSAGE;
}

/* Create a refresh packet for the given message ID.  You can assume
 * that packed is a buffer of size PACKET_SIZE.
 *
 * You should start by implementing this method!
 *
 * Returns the message type.
 */
int pack_refresh(void *packed, int message_id) {
  
  void *refresh_packer = packed;
  *(int *)refresh_packer = REFRESH;//this indicates that this packet is a refresh packedt
  
  refresh_packer += sizeof(int);//move this pointer along by sizeof(int) bytes (4)
  
  char *name = "arflierl";//my UBID
  
  for (int i = 0; i < 8; i++) {
    *(char *)refresh_packer = *(name + i);//entering my UBID
    refresh_packer++;
  }
  
  for (int i = 8; i < NAME_SIZE; i++) {
    *(char *)refresh_packer = '\0';//padding the remaining NAME_SIZE bytes with ASCII NULL
    refresh_packer++;
  }

  *(int *)refresh_packer = message_id;//assigning the message_id as "Last message"

  refresh_packer += sizeof(int);//move this void pointer to the end of this chunk
  
  return REFRESH;
}
