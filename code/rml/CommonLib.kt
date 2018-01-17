package rml

import rml.funcs.ArrayGet
import rml.funcs.CreateArray
import rml.funcs.CreateMap
import rml.funcs.Print

object CommonLib {

    fun addFuncsTo(scope: Context?) {
        scope?.addFunc(Print(scope))
        scope?.addFunc(CreateArray(scope))
        scope?.addFunc(CreateMap(scope))
        scope?.addFunc(ArrayGet(scope))
    }
}