package rml

import rml.funcs.*

object CommonLib {

    fun addFuncsTo(scope: Context?) {
        scope?.addFunc(Print(scope))
        scope?.addFunc(Println(scope))
        scope?.addFunc(FormString(scope))
        scope?.addFunc(CreateArray(scope))
        scope?.addFunc(CreateMap(scope))
    }
}