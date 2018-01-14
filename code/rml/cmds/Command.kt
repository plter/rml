package rml.cmds

import rml.Scope

abstract class Command(parent: Scope?) : Scope(parent) {

    abstract fun execute(): Var?
}