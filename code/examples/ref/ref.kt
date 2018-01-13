import rml.RMLReader

fun main(args: Array<String>) {

    val s = readFile("app.xml")
    val r = RMLReader(s)
    r.read()
    r.run()
}