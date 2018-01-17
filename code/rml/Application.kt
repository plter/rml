package rml

class Application(parent: Context?) : Context(parent) {

    init {
        CommonLib.addFuncsTo(this)
    }

    fun run() {
        getFunc("main")?.execute(ArrayList())
    }
}