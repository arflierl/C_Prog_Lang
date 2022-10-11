#include <stdlib.h>
#include <string.h>

#include "serialize.h"

/* Unpack the given message into the buffer unpacked.  You can assume
 * that packed points to a message buffer large enough to hold the
 * message described therein, but you cannot assume that the message is
 * otherwise valid.  You can assume that unpacked points to a character
 * buffer large enough to store the unpacked message, if it is a valid
 * message.
 *
 * Returns the message type that was unpacked, or -1 if it is invalid.
 */
int unpack(char *unpacked, void *packed) {
  
  //unpack a message
  if (*(int *)packed == MESSAGE) {
    void *get_UBID = packed;
    void *get_msg = packed;
    //unpack the UBID
    get_UBID += sizeof(int);

    while (*(char *)get_UBID != '\0') {
      *(unpacked) = *(char *)get_UBID;
      unpacked++;
      get_UBID++;
    }

    *(unpacked) = ':';
    unpacked++;

    *(unpacked) = ' ';
    unpacked++;

    get_msg += sizeof(int);
    get_msg += NAME_SIZE;
    size_t string_length = *(size_t *)get_msg;
    if (string_length > MAX_MESSAGE_SIZE) {
      return -1;
    }
    get_msg += sizeof(size_t);
    get_msg += sizeof(size_t);
    int msg_chars = 0;
    for (size_t i = 0; i < string_length; i++) {
      *(unpacked) = *(char *)get_msg;
      if (*(char *)get_msg != ' ') {
	msg_chars++;
      }
      unpacked++;
      get_msg++;
    }

    if (msg_chars == 0) { //if message is only white space
      return -1;
    }
    
    *(char *)unpacked = '\0';

    return MESSAGE;
  }
  
  //unpack a status
  if (*(int *)packed == STATUS) {
    void *get_UB = packed;
    void *get_status = packed;
    get_UB += sizeof(int);

    int UBCHARS = 0;
    while (*(char *)get_UB != '\0') {
      *(unpacked) = *(char *)get_UB;
      if (*(char *)get_UB != ' ') {
	UBCHARS++;
      }
      unpacked++;
      get_UB++;
    }

    if (UBCHARS == 0) {
      return -1;
    }

    *(unpacked) = ' ';
    unpacked++;

    get_status += sizeof(int);
    get_status += NAME_SIZE;
    size_t status_length = *(size_t *)get_status;
    if (status_length > MAX_MESSAGE_SIZE) {
      return -1;
    }
    get_status += sizeof(size_t);
    get_status += sizeof(size_t);


    int status_chars = 0;
    for (size_t i = 0; i < status_length; i++) {
      *(unpacked) = *(char *)get_status;
      if (*(char *)get_status != ' ') {
	status_chars++;
      }
      unpacked++;
      get_status++;
    }

    if (status_chars == 0) {
      return-1;
    }

    *(char *)unpacked = '\0';

    return STATUS;

  }

  //unpack a labeled packed
  if (*(int *)packed == LABELED) {
    void *get_ID = packed;
    void *get_target = packed;
    void *get_MSG = packed;

    get_ID += sizeof(int);

    while (*(char *)get_ID != '\0') {
      *(unpacked) = *(char *)get_ID;
      unpacked++;
      get_ID++;
    }
    
    *(unpacked) = ':';
    unpacked++;
    
    *(unpacked) = ' ';
    unpacked++;

    *(unpacked) = '@';
    unpacked++;

    get_target += sizeof(int);
    get_target += NAME_SIZE;
    size_t mention_length = *(size_t *)get_target;
    get_target += sizeof(size_t); //skipping over message length
    size_t target_length = *(size_t *)get_target;

    int data_length = mention_length + target_length;
    if (data_length > MAX_MESSAGE_SIZE) {
      return -1; //sum of data lengths field cannot exceed max_msg_sz
    }
    get_target += sizeof(size_t); //skipping over target length
    get_target += sizeof(size_t); //skipping over the 0
    get_target += mention_length; //skipping over mention_length bytes
    //now I can get the chars that make up the target

    int target_chars = 0;
    for (size_t i = 0; i < target_length; i++) {
      *(unpacked) = *(char *)get_target;
      if (*(char *)get_target != ' ') {
	target_chars++;
      }
      unpacked++;
      get_target++;
    }

    if (target_chars == 0) {
      return -1;
    }

    *(unpacked) = ' ';
    unpacked++;

    get_MSG += sizeof(int); //skipping over msg type
    get_MSG += NAME_SIZE; //skipping over name_size bytes
    get_MSG += sizeof(size_t); //skipping over msg length
    get_MSG += sizeof(size_t); //skipping over target length
    get_MSG += sizeof(size_t); //skipping over the 0

    //now I can get the chars that make up the message

    int label_msg_chars = 0;
    for (size_t i = 0; i < mention_length; i++) {
      *(unpacked) = *(char *)get_MSG;
      if (*(char *)get_MSG != ' ') {
	label_msg_chars++;
      }
      unpacked++;
      get_MSG++;
    }

    if (label_msg_chars == 0) {
      return -1;
    }
    
    *(unpacked) = '\0';

    return LABELED;
  }
  
  return -1;
}

/* Unpack the given packed message into the given statistics structure.
 * You can assume that packed points to a message buffer large enough to
 * hold the statistics message, but you cannot assume that it is
 * otherwise valid.  You can assume that statistics points to a
 * statistics structure.
 *
 * Returns the message type that was unpacked, or -1 if it is invalid.
 */
int unpack_statistics(struct statistics *statistics, void *packed) {
  void *get_stats = packed;

  //check that this is a STATISTICS MESSAGE
  if (*(int *)packed != STATISTICS) {
    return -1;
  }

  get_stats += sizeof(int); //move to sender

  void *get_sender = get_stats; 

  int place_holder = 0;
  int sender_chars = 0;
  while (place_holder < NAME_SIZE) {
    statistics->sender[place_holder] = *(char *)get_sender; //assigning sender chars to array
    if (*(char *)get_sender != ' ') {
      sender_chars++;
    }
    get_sender++;
    place_holder++;
  }

  if (sender_chars == 0) { //if UBID is all whitespace, it is invalid
    return -1;
  }

  
  statistics->sender[place_holder] = '\0'; //NULL TERMINATOR

  get_stats += NAME_SIZE; //move to most active

  void *get_most_active = get_stats; 

  int hold = 0;
  int most_chars = 0;
  while (hold < NAME_SIZE) {
    statistics->most_active[hold] = *(char *)get_most_active;
    if (*(char *)get_most_active != ' ') {
      most_chars++;
    }
    get_most_active++;
    hold++;
  }

  if (most_chars == 0) { //if most active is all whitespace, it is invalid
    return -1;
  }

  statistics->most_active[hold] = '\0'; //NULL TERMINATOR

  get_stats += NAME_SIZE; //move to Most Active Count

  statistics->most_active_count = *(int *)get_stats; //assign most act cnt

  get_stats += sizeof(int); //move to invalid count

  statistics->invalid_count = *(long *)get_stats; //assign invalid count

  get_stats += sizeof(long); //move to refresh count

  statistics->refresh_count = *(long *)get_stats; //assign refresh count

  get_stats += sizeof(long); //move to message count

  statistics->messages_count = *(int *)get_stats;//assign message count 

  
  return STATISTICS; //returns message type that was unpacked
}
