from pydantic import BaseModel, Field, ValidationError
class BookEntry(BaseModel):
    title: str = Field(..., min_length=1, max_length=100)
    price: float = Field(..., gt=0)
    authors: list[str] = Field(default_factory=list)
    rating: float | None = Field(default=None, ge=0, le=10)

def format_book(book: BookEntry) -> str:
    rating_str = f" | 评分:{book.rating:.2f}" if book.rating is not None else ""
    return f"《{book.title}》| ￥{book.price:.2f} | 作者:{'、'.join(book.authors)}{rating_str}"

book = BookEntry(title="三国演义", price=59.9, authors=["罗贯中"], rating=9.5)
print(format_book(book))

def parse_books(raw: list[dict]) -> list[BookEntry]:
    books: list[BookEntry] = []
    for index, item in enumerate(raw):
        try:
            book = BookEntry(**item)
            print(f"第{index+1}行解析成功: {book.model_dump_json()} {book.price *2 = }")
            books.append(book)
        except ValidationError as e:
            print(f"第{index+1}行解析失败: {e}")
    return books

raw = [{"title": "三国演义", "price": 59.9, "authors": ["罗贯中"], "rating": 9.5}, {"title": "西游记", "price": -69.9, "authors": ["吴承恩"], "rating": 99}]
books = parse_books(raw)
print(books)

