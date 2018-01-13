package rml

class Application(parent: Scope?) : Scope(parent) {

    init {
        CommonLib.addFuncsTo(this)
    }

    fun run() {
        getFunc("main")?.execute(ArrayList())
    }
}