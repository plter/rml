package rml

abstract class Command(parent: Scope?) : Scope(parent) {

    abstract fun execute(): Var?
}