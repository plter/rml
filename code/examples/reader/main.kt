import rml.XMLReader


class Reader(source: String?) : XMLReader(source) {
    override fun elementStart(tagName: String, attributes: Map<String, String>) {
        println("elementStart $tagName,attrs $attributes")
    }

    override fun elementEnd(tagName: String) {
        println("elementEnd $tagName")
    }

    override fun commentContent(content: String) {
        println("commentContent $content")
    }
}

fun main(args: Array<String>) {
    val s = readFile("data.xml")
    val reader = Reader(s)
    reader.read()
}