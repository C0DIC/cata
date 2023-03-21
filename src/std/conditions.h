//
//
//    conditions.h
//    Created by C0DIC, 21/03/2023
//
//    Example:    
//            if true
//                write "True"
//            else
//                write "False"
//            end
//
//            if true
//                write "True"
//            end
//

#ifndef CATA_CONDITIONS_H
#define CATA_CONDITIONS_H

int if_condition(CataVar condition, size_t end_pos, size_t *pos);

#endif

#ifdef  CATA_CONDITIONS

int if_condition(CataVar condition, size_t end_pos, size_t *pos) {
    if (condition.value.as_int) {
        return 1;
    } else {
        *pos = end_pos;
    }

    return 0;
};

#endif