//
//  RMLObject.h
//  rml
//
//  Created by plter on 9/6/14.
//  Copyright (c) 2014 plter. All rights reserved.
//

#ifndef rml_RMLObject_h
#define rml_RMLObject_h

namespace rml {
    
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    class Object{
        
    public:
        Object(){
            _retainCount = 1;
        };
        
        inline int retainCount(){
            return _retainCount;
        };
        
        inline void retain(){
            _retainCount++;
        }
        
        inline void release(){
            _retainCount--;
            
            if (_retainCount<=0) {
                delete this;
            }
        }
        
        virtual ~Object(){
        };
        
    private:
        int _retainCount;
    };//class Object end
}

#endif
