package rml

import rml.funcs.CreateArray
import rml.funcs.CreateMap
import rml.funcs.Print

object CommonLib {

    fun addFuncsTo(scope: Scope?) {
        scope?.addFunc(Print(scope))
        scope?.addFunc(CreateArray(scope))
        scope?.addFunc(CreateMap(scope))
    }
}