package rml

import rml.funcs.Print

object CommonLib {

    fun addFuncsTo(scope: Scope?) {
        scope?.addFunc(Print(scope))
    }
}